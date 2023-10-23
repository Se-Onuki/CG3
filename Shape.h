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