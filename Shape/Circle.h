#pragma once
#include "IShape.h"

class Circle final :public IShape {
public:
	Circle() = default;
	~Circle() = default;

	void Size() override;
	void Draw() const override;

	void SetRadius(const float radius);

private:
	float radius_;
};