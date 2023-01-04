#pragma once
#include <cstddef>

struct RGB {
	std::byte b;
	std::byte g;
	std::byte r;
	RGB(const unsigned int& colorcode) :
		b(std::byte(colorcode & 0xff)),
		g(std::byte((colorcode >> 8) & 0xff)),
		r(std::byte((colorcode >> 16) & 0xff)) {}
	// RGB& operator=(const ARGB& argb)&;
	RGB& operator=(const RGB& rgb)& {
		this->r = rgb.r;
		this->g = rgb.g;
		this->b = rgb.b;
		return *this;
	}
};

struct ARGB {
	std::byte b;
	std::byte g;
	std::byte r;
	std::byte a;
	ARGB& operator=(const ARGB& argb)& {
		this->a = argb.a;
		this->r = argb.r;
		this->g = argb.g;
		this->b = argb.b;
		return *this;
	}

	ARGB& operator=(const RGB& rgb)& {
		this->r = rgb.r;
		this->g = rgb.g;
		this->b = rgb.b;
		return *this;
	}
};
