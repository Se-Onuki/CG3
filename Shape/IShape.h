#pragma once

struct Vec2 {
	float x;
	float y;
};

class IShape {
public:
	IShape() = default;
	virtual ~IShape() = default;

	virtual void Size() = 0;
	virtual void Draw() const = 0;
protected:

	float size_ = {};

private:
};