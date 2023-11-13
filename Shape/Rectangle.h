#pragma once
#include "IShape.h"

class Rectangle final :public IShape {
public:
	Rectangle() = default;
	~Rectangle() = default;

	void Size() override;
	void Draw() const override;

	void SetRadius(const Vec2 &vec);

private:
	Vec2 radius_;
};
