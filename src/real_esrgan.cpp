#include "functions.h"
#include "ncnn.h"

std::pair<cv::Mat, ErrorMsg> inference(const cv::Mat image, const ncnn::Net* model);

cv::Mat to_ocv(const ncnn::Mat& result) {

	cv::Mat cv_result32f = cv::Mat::zeros(result.h, result.w, CV_32FC3);
	cv::Mat cv_result8b;

	for (int y = 0; y < result.h; ++y)
		for (int x = 0; x < result.w; ++x) {
			cv_result32f.at<cv::Vec3f>(y, x)[0] = result.channel(2)[x + result.w * y];
			cv_result32f.at<cv::Vec3f>(y, x)[1] = result.channel(1)[x + result.w * y];
			cv_result32f.at<cv::Vec3f>(y, x)[2] = result.channel(0)[x + result.w * y];
		}

	cv_result32f.convertTo(cv_result8b, CV_8UC3, 255.0, 0.0);
	return cv_result8b;
}

ErrorMsg real_esrgan(ARGB* image, const int& width, const int& height, const RectArea& extend, const std::string& modelpath_noext) {

	if (width != 4 * (width - (extend.left + extend.right))) {
		return "invalid width: extended != 4x origin";
	}
	else if (height != 4 * (height - (extend.top + extend.bottom))) {
		return "invalid height: extended != 4x origin";
	}

	auto origin_color = color_to_cvmat(image, width, height, extend);
	auto origin_alpha = just_alpha_to_cvmat(image, width, height, extend);

	// load model
	static std::map<std::string, std::shared_ptr<ncnn::Net>> models = {};
	std::shared_ptr<ncnn::Net> net;
	if (models.contains(modelpath_noext)) {
		net = models[modelpath_noext];
	}
	else {
		net = std::make_shared<ncnn::Net>();
		FILE* fp;
		std::string path;
		
		path = (modelpath_noext + ".param");
		fopen_s(&fp, path.c_str(), "r");
		if (fp == nullptr) {
			return ".param file not exist";
		}
		fclose(fp);
		auto res = net->load_param(path.c_str());
		if (res < 0) {
			return "open .param file failed";
		}

		path = (modelpath_noext + ".bin");
		fopen_s(&fp, path.c_str(), "r");
		if (fp == nullptr) {
			return ".bin file not exist";
		}
		fclose(fp);
		res = net->load_model(path.c_str());
		if (res < 0) {
			return "open .bin file failed";
		}

		net->opt.use_vulkan_compute = false;
		net->opt.num_threads = 4;

		models.insert(std::make_pair(modelpath_noext, net));
	}

	// inference
	auto result_color = inference(origin_color, net.get());
	if (result_color.second != "") {
		return result_color.second;
	}
	auto result_alpha = inference(origin_alpha, net.get());
	if (result_color.second != "") {
		return result_color.second;
	}

	for (int i = 0, l = width * height; i < l; ++i) {
		image[i].a = std::byte(0);
		image[i].r = std::byte(0);
		image[i].g = std::byte(0);
		image[i].b = std::byte(0);
	}

	for (int y = 0, h = min(height, min(result_color.first.rows, result_alpha.first.rows)); y < h; ++y)
		for (int x = 0, w = min(width, min(result_color.first.cols, result_alpha.first.cols)); x < w; ++x) {
			image[x + y * width].b = std::byte(result_color.first.at<cv::Vec3b>(y, x)[0]);
			image[x + y * width].g = std::byte(result_color.first.at<cv::Vec3b>(y, x)[1]);
			image[x + y * width].r = std::byte(result_color.first.at<cv::Vec3b>(y, x)[2]);
			int alpha = 1;
			alpha += result_alpha.first.at<cv::Vec3b>(y, x)[0];
			alpha += result_alpha.first.at<cv::Vec3b>(y, x)[1];
			alpha += result_alpha.first.at<cv::Vec3b>(y, x)[2];
			image[x + y * width].a = std::byte(alpha / 3);
		}

	return "";
}

std::pair<cv::Mat, ErrorMsg> inference(const cv::Mat image, const ncnn::Net* model) {
	
	const int tile_size = 400;
	const int tile_padding = 10;
	const int scale = 4;

	cv::Mat padding_image;

	// pre-process
	int padding_image_w = image.cols % 2, padding_image_h = image.rows % 2;
	cv::copyMakeBorder(image, padding_image, 0, padding_image_w, 0, padding_image_h, cv::BORDER_CONSTANT, cv::Scalar(0));

	cv::Mat result(padding_image.rows * scale, padding_image.cols * scale, CV_8UC3);

	// tile-splitted compute
	for (int y_tile = 0, h_tile = std::ceil((float)padding_image.rows / tile_size); y_tile < h_tile; ++y_tile)
		for (int x_tile = 0, w_tile = std::ceil((float)padding_image.cols / tile_size); x_tile < w_tile; ++x_tile) {

			// input rect area
			int input_top = y_tile * tile_size;
			int input_bottom = min(input_top + tile_size, padding_image.rows);
			int input_left = x_tile * tile_size;
			int input_right = min(input_left + tile_size, padding_image.cols);

			// input-padding rect area
			int input_top_padding = max(input_top - tile_padding, 0);
			int input_bottom_padding = min(input_bottom + tile_padding, padding_image.rows);
			int input_left_padding = max(input_left - tile_padding, 0);
			int input_right_padding = min(input_right + tile_padding, padding_image.cols);

			int input_tile_w = input_right - input_left;
			int input_tile_h = input_bottom - input_top;
			int input_tile_padding_w = input_right_padding - input_left_padding;
			int input_tile_padding_h = input_bottom_padding - input_top_padding;

			cv::Mat input_tile = padding_image(cv::Rect(input_left_padding, input_top_padding, input_tile_padding_w, input_tile_padding_h)).clone();

			// inference
			const float norm_vals[3] = { 1.0 / 255.0, 1.0 / 255.0 , 1.0 / 255.0 };
			ncnn::Mat ncnn_in = ncnn::Mat::from_pixels(input_tile.data, ncnn::Mat::PIXEL_BGR2RGB, input_tile_padding_w, input_tile_padding_h);
			ncnn::Mat ncnn_out;
			ncnn_in.substract_mean_normalize(0, norm_vals);
			ncnn::Extractor extractor = model->create_extractor();
			if (extractor.input("data", ncnn_in) != 0) {
				return std::make_pair(result, "failed set input tile");
			}
			extractor.extract("output", ncnn_out);

			cv::Mat output_tile = to_ocv(ncnn_out);
			if (output_tile.cols != input_tile.cols * scale || output_tile.rows != input_tile.rows * scale) {
				return std::make_pair(result, "result scale is not x4 scale: " + 
					std::format("{}x{} > {}x{}", input_tile.cols, input_tile.rows, output_tile.cols, output_tile.rows));
			}

			// output rect area
			int output_top = input_top * scale;
			int output_bottom = input_bottom * scale;
			int output_left = input_left * scale;
			int output_right = input_right * scale;

			int output_tile_top = (input_top - input_top_padding) * scale;
			int output_tile_bottom = output_tile_top + input_tile_h * scale;
			int output_tile_left = (input_left - input_left_padding) * scale;
			int output_tile_right = (output_tile_left + input_tile_w * scale);
			
			cv::Rect tile_rect = cv::Rect(output_tile_left, output_tile_top,
				output_tile_right - output_tile_left,
				output_tile_bottom - output_tile_top);

			cv::Rect out_rect = cv::Rect(output_left, output_top,
				output_right - output_left,
				output_bottom - output_top);

			output_tile(tile_rect).copyTo(result(out_rect));
		}

	return std::make_pair(result, no_error);
}
