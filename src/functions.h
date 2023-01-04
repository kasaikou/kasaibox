#pragma once

#include "type.h"
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using ErrorMsg = std::string;

ErrorMsg opencv_binalization(ARGB* image, const int& width, const int& height, const RGB& dark, const RGB& blight, const int& mode);
