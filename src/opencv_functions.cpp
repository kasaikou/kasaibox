#include "functions.h"

cv::Mat color_to_cvmat(ARGB* image, const int& width, const int& height, const bool& monochrome) noexcept {

	if (monochrome) {
	} else {
		cv::Mat rgb = cv::Mat::zeros(width, height, CV_8UC3);
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				rgb.at<cv::Vec3b>(x, y)[0] = uchar(image[x + y * width].b);
				rgb.at<cv::Vec3b>(x, y)[1] = uchar(image[x + y * width].g);
				rgb.at<cv::Vec3b>(x, y)[2] = uchar(image[x + y * width].r);
			}
		return rgb;
	}
}

cv::Mat color_to_cvmat(ARGB* image, const int& width, const int& height, const RectArea& padding, const bool& monochrome) noexcept {
	if (monochrome) {

	} else {
		cv::Mat rgb = cv::Mat::zeros(width - (padding.left + padding.right), height - (padding.top + padding.bottom), CV_8UC3);
		for (int y_img = padding.top, h_img = height - padding.bottom, y_mat = 0; y_img < h_img; ++y_img, ++y_mat)
			for (int x_img = padding.left, w_img = width - padding.right, x_mat = 0; x_img < w_img; ++x_img, ++x_mat) {
				rgb.at<cv::Vec3b>(x_mat, y_mat)[0] = uchar(image[x_img + y_img * width].b);
				rgb.at<cv::Vec3b>(x_mat, y_mat)[1] = uchar(image[x_img + y_img * width].g);
				rgb.at<cv::Vec3b>(x_mat, y_mat)[2] = uchar(image[x_img + y_img * width].r);
			}
		return rgb;
	}
}

void assign_cvmat(ARGB* image, const int& width, const int& height, cv::Mat mat) {
	
	switch (mat.type()) {
	case CV_8UC3:
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				image[x + y * width].b = std::byte(mat.at<cv::Vec3b>(x, y)[0]);
				image[x + y * width].g = std::byte(mat.at<cv::Vec3b>(x, y)[1]);
				image[x + y * width].r = std::byte(mat.at<cv::Vec3b>(x, y)[2]);
			}
		return;
	case CV_8UC1:
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				image[x + y * width].b = std::byte(mat.at<cv::Vec<uchar, 1>>(x, y)[0]);
				image[x + y * width].g = std::byte(mat.at<cv::Vec<uchar, 1>>(x, y)[0]);
				image[x + y * width].r = std::byte(mat.at<cv::Vec<uchar, 1>>(x, y)[0]);
			}
		return;
	default:
		return;
	}
}

ErrorMsg opencv_binalization(ARGB* image, const int& width, const int& height, const RGB& dark, const RGB& blight, const int& mode) {		
	cv::Mat src = to_cvmat(image, width, height), dest(width, height, CV_8UC3);
	cv::threshold(src, dest, 128, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	assign_cvmat(image, width, height, src);
	return "";
}
