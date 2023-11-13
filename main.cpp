#include <iostream>
#include <memory>
#include <array>
#include <assert.h>
#include "Shape/IShape.h"
#include "Shape/Rectangle.h"
#include "Shape/Circle.h"

int main(void) {

	std::array<std::unique_ptr<IShape>, 2u> shapes = {};
	shapes[0u] = std::make_unique<Rectangle>();
	shapes[1u] = std::make_unique<Circle>();

	auto *const rectangle = dynamic_cast<Rectangle *>(shapes[0u].get());
	assert(rectangle && "型が一致しません");
	if (rectangle) {
		rectangle->SetRadius(Vec2{ 10.f,10.f });
	}

	auto *const circle = dynamic_cast<Circle *>(shapes[1u].get());
	assert(circle && "型が一致しません");
	if (circle) {
		circle->SetRadius(25.f);
	}

	for (auto &shape : shapes) {
		shape->Size();
		shape->Draw();
	}

	return 0;
}