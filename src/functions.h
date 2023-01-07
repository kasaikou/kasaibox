#pragma once

#include "type.h"
#include <string>
#include <map>
#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using ErrorMsg = std::string;
static ErrorMsg no_error = "";
ErrorMsg make_error(const std::string& msg);

cv::Mat color_to_cvmat(ARGB* image, const int& width, const int& height, const bool& monochrome = false) noexcept;
cv::Mat color_to_cvmat(ARGB* image, const int& width, const int& height, const RectArea& padding, const bool& monochrome = false) noexcept;
cv::Mat just_alpha_to_cvmat(ARGB* image, const int& width, const int& height, const RectArea& padding, const bool& monochrome = false) noexcept;
void assign_cvmat(ARGB* image, const int& width, const int& height, cv::Mat mat);


ErrorMsg opencv_binalization(ARGB* image, const int& width, const int& height, const RGB& dark, const RGB& blight, const int& mode);
ErrorMsg real_esrgan(ARGB* image, const int& width, const int& height, const RectArea& extend, const std::string& modelpath_noext);
