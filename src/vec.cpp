#include "vec.h"

Vec::Vec() {
	x = y = 0;
}

Vec::Vec(float x_, float y_) {
	x = x_;
	y = y_;
}

float Vec::mag() const {
	return sqrt(x*x+y*y);
}

void Vec::normalize() {
	operator*=(1/mag());
}

Vec Vec::normalized() const {
	Vec v_(x, y);
	v_.normalize();
	return v_;
}

float Vec::dir() const {
	return -1*(atan2(-y, x));
}

float Vec::dot(const Vec& v) const {
	return x*v.x + y*v.y;
}

Vec Vec::lerp(const Vec& v, float t) const {
	return Vec(x, y) + (v-Vec(x, y))*t;
}

void Vec::head_to(float a) {
	float d_ = mag();
	x = cos(a)*d_;
	y = sin(a)*d_;
}

void Vec::rotate(float a) {
	head_to(dir()+a);
}

Vec Vec::operator+(const Vec& v) const {
	return Vec(x + v.x, y + v.y);
}

Vec Vec::operator-(const Vec& v) const {
	return Vec(x - v.x, y - v.y);
}

Vec Vec::operator*(const float s) const {
	return Vec(x*s, y*s);
}

Vec Vec::operator/(const float s) const {
	return Vec(x/s, y/s);
}

Vec Vec::operator+(const float s) const {
	Vec v_(x, y);
	v_.normalize();
	v_ = v_ * (mag()+s);
	return v_;
}

Vec Vec::operator-(const float s) const {
	Vec v_(x, y);
	v_.normalize();
	v_ = v_ * (mag()-s);
	return v_;
}

void Vec::operator=(const Vec& v) {
	//std::cout << &v << "\n";
	x = v.x;
	y = v.y;
}

void Vec::operator+=(const Vec& v) {
	x += v.x;
	y += v.y;
}

void Vec::operator-=(const Vec& v) {
	x -= v.x;
	y -= v.y;
}

void Vec::operator*=(const float s) {
	x *= s;
	y *= s;
}

void Vec::operator/=(const float s) {
	x /= s;
	y /= s;
}

void Vec::operator=(const float s) {
	normalize();
	operator*=(s);
}

void Vec::operator+=(const float s) {
	float d_ = mag();
	normalize();
	operator*=(d_+s);
}

void Vec::operator-=(const float s) {
	float d_ = mag();
	normalize();
	operator*=(d_-s);
}

int sign(int x) {
	if (x > 0) {return 1;}
	if (x < 0) {return -1;}
	return 0;
}

bool aabb(Vec tl1, Vec br1, Vec tl2, Vec br2) {
  return (!(br1.x <= tl2.x || tl1.x >= br2.x) && !(br1.y <= tl2.y || tl1.y >= br2.y));
}

bool point_in_rectangle(Vec p, Vec tl, Vec br) {
	return (p.x >= tl.x && p.x <= br.x) && (p.y >= tl.y && p.y <= br.y);
}

float lerp(float a, float b, float t) {
	return a + (b-a)*t;
}
