#include "functions.h"

cv::Mat color_to_cvmat(ARGB* image, const int& width, const int& height, const bool& monochrome) noexcept {

	if (monochrome) {
	} else {
		cv::Mat rgb = cv::Mat::zeros(height, width, CV_8UC3);
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				rgb.at<cv::Vec3b>(y, x)[0] = uchar(image[x + y * width].b);
				rgb.at<cv::Vec3b>(y, x)[1] = uchar(image[x + y * width].g);
				rgb.at<cv::Vec3b>(y, x)[2] = uchar(image[x + y * width].r);
			}
		return rgb;
	}
}

cv::Mat color_to_cvmat(ARGB* image, const int& width, const int& height, const RectArea& padding, const bool& monochrome) noexcept {
	if (monochrome) {

	} else {
		cv::Mat rgb = cv::Mat::zeros(height - (padding.top + padding.bottom), width - (padding.left + padding.right), CV_8UC3);
		for (int y_img = padding.top, h_img = height - padding.bottom, y_mat = 0; y_img < h_img; ++y_img, ++y_mat)
			for (int x_img = padding.left, w_img = width - padding.right, x_mat = 0; x_img < w_img; ++x_img, ++x_mat) {
				rgb.at<cv::Vec3b>(y_mat, x_mat)[0] = uchar(image[x_img + y_img * width].b);
				rgb.at<cv::Vec3b>(y_mat, x_mat)[1] = uchar(image[x_img + y_img * width].g);
				rgb.at<cv::Vec3b>(y_mat, x_mat)[2] = uchar(image[x_img + y_img * width].r);
			}
		return rgb;
	}
}

cv::Mat just_alpha_to_cvmat(ARGB* image, const int& width, const int& height, const RectArea& padding, const bool& monochrome) noexcept {
	if (monochrome) {

	} else {
		cv::Mat rgb = cv::Mat::zeros(height - (padding.top + padding.bottom), width - (padding.left + padding.right), CV_8UC3);
		for (int y_img = padding.top, h_img = height - padding.bottom, y_mat = 0; y_img < h_img; ++y_img, ++y_mat)
			for (int x_img = padding.left, w_img = width - padding.right, x_mat = 0; x_img < w_img; ++x_img, ++x_mat) {
				rgb.at<cv::Vec3b>(y_mat, x_mat)[0] = uchar(image[x_img + y_img * width].a);
				rgb.at<cv::Vec3b>(y_mat, x_mat)[1] = uchar(image[x_img + y_img * width].a);
				rgb.at<cv::Vec3b>(y_mat, x_mat)[2] = uchar(image[x_img + y_img * width].a);
			}
		return rgb;
	}
}

void assign_cvmat(ARGB* image, const int& width, const int& height, cv::Mat mat) {
	
	switch (mat.type()) {
	case CV_8UC3:
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				image[x + y * width].b = std::byte(mat.at<cv::Vec3b>(y, x)[0]);
				image[x + y * width].g = std::byte(mat.at<cv::Vec3b>(y, x)[1]);
				image[x + y * width].r = std::byte(mat.at<cv::Vec3b>(y, x)[2]);
			}
		return;
	case CV_8UC1:
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				image[x + y * width].b = std::byte(mat.at<cv::Vec<uchar, 1>>(y, x)[0]);
				image[x + y * width].g = std::byte(mat.at<cv::Vec<uchar, 1>>(y, x)[0]);
				image[x + y * width].r = std::byte(mat.at<cv::Vec<uchar, 1>>(y, x)[0]);
			}
		return;
	default:
		return;
	}
}

ErrorMsg opencv_binalization(ARGB* image, const int& width, const int& height, const RGB& dark, const RGB& blight, const int& mode) {		
	cv::Mat src = color_to_cvmat(image, width, height), dest(width, height, CV_8UC3);
	cv::threshold(src, dest, 128, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	assign_cvmat(image, width, height, src);
	return "";
}
