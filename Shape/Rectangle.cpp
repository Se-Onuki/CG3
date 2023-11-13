#include "Rectangle.h"
#include <iostream>

void Rectangle::Size() {
	size_ = (radius_.x * 2.f) * (radius_.y * 2.f);
}

void Rectangle::Draw() const {
	std::cout << "半径[x: " << radius_.x << ", y: " << radius_.y << "]の四角形の面積は" << size_ << std::endl;
}

void Rectangle::SetRadius(const Vec2 &vec) {
	radius_ = vec;
}
