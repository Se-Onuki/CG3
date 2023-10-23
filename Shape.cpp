#include "Shape.h"
#include <iostream>
#include <numbers>

void Rectangle::Size() {
	size_ = (radius_.x * 2.f) * (radius_.y * 2.f);
}

void Rectangle::Draw() const {
	std::cout << "半径[x: " << radius_.x << ", y: " << radius_.y << "]の四角形の面積は" << size_ << std::endl;
}

void Rectangle::SetRadius(const Vec2 &vec) {
	radius_ = vec;
}

void Circle::Size() {
	size_ = radius_ * radius_ * std::numbers::pi_v<float>;
}

void Circle::Draw() const {
	std::cout << "半径[ " << radius_ << " ]の円の面積は" << size_ << std::endl;
}

void Circle::SetRadius(const float radius) {
	radius_ = radius;
}