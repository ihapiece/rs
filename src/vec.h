#pragma once
#include <cmath>

struct Vec {
	float x;
	float y;

	Vec();

	Vec(float x_, float y_);

	float mag() const;
	void normalize();
	Vec normalized() const;
	float dir() const;
	float dot(const Vec& v) const;
	Vec lerp(const Vec& v, float t) const;
	void head_to(float a);
	void rotate(float a);

	Vec operator+(const Vec& v) const;
	Vec operator-(const Vec& v) const;
	Vec operator*(const float s) const;
	Vec operator/(const float s) const;
	Vec operator+(const float s) const;
	Vec operator-(const float s) const;

	void operator=(const Vec& v);
	void operator+=(const Vec& v);
	void operator-=(const Vec& v);
	void operator*=(const float s);
	void operator/=(const float s);
	void operator=(const float s);
	void operator+=(const float s);
	void operator-=(const float s);
};

int sign(int x);
bool aabb(Vec tl1, Vec br1, Vec tl2, Vec br2);
bool point_in_rectangle(Vec p, Vec tl, Vec br);
float lerp(float a, float b, float t);
