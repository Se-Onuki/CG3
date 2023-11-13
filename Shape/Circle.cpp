#include "Circle.h"
#include <iostream>
#include <numbers>

void Circle::Size() {
	size_ = radius_ * radius_ * std::numbers::pi_v<float>;
}

void Circle::Draw() const {
	std::cout << "半径[ " << radius_ << " ]の円の面積は" << size_ << std::endl;
}

void Circle::SetRadius(const float radius) {
	radius_ = radius;
}