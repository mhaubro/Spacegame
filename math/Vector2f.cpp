//Author: MG

#include "Vector2f.h"
#include "math.h"
#include "GD2.h"

Vector2f::Vector2f() :
		x(0), y(0) {
}

Vector2f::Vector2f(float x, float y) :
		x(x), y(y) {
}

Vector2f::Vector2f(const Vector2f & v) :
		x(v.x), y(v.y) {
}

Vector2f::Vector2f(Vector2f & v) :
		x(v.x), y(v.y) {
}

Vector2f::~Vector2f() {
}

Vector2f FromAngle(float length, float angle) {
	return Vector2f(length * cosf(angle), -(length * sinf(angle)));
}
float Vector2f::dotProduct(Vector2f extv) {
	return x * extv.x + y * extv.y;
}

float Vector2f::crossproduct(Vector2f arg) {
	return (this->x * arg.y - this->y * arg.x);
}

Vector2f Vector2f::projectAt(Vector2f arg) {
	Vector2f normalArg = arg.normalized();
	return normalArg * normalArg.dotProduct(*this);
}

float Vector2f::scalarProjectAt(Vector2f arg) {
	return arg.normalized().dotProduct(*this);
}

Vector2f Vector2f::vertexTransformed(Vector2f positionTransform,
		float rotationTransform) {
	return Vector2f(
			FromAngle(1, rotationTransform) * x
					+ FromAngle(1, rotationTransform - PI / 2) * y)
			+ positionTransform;
}

float Vector2f::length() {
	return sqrtf((x * x) + (y * y));
}

float Vector2f::angle() {//Vinkel i klassiske radianer + 90 grader -> 0-punkt i (0,1), 90 grader i (-1, 0) etc.
	if (x == 0 && y == 0)
		return 0;
	float a = atan2f(-y, x);

	while (a < 0)
		a += PI * 2;
	while (a > PI * 2)
		a -= PI * 2;
	return a;
}

void Vector2f::wrap(Vector2f min, Vector2f max) {
	Vector2f d = max - min;
	while (x > max.x) {
		x -= d.x;
	}
	while (x < min.x) {
		x += d.x;
	}
	while (y > max.y) {
		y -= d.y;
	}
	while (y < min.y) {
		y += d.y;
	}
}
Vector2f Vector2f::normalized() {
	float len = this->length();
	if (len != 0) {
		return Vector2f(x / len, y / len);
	}
	return Vector2f(1,0);
}

Vector2f Vector2f::leftNormal() {
	return Vector2f(-y, x);
}

Vector2f Vector2f::rightNormal() {
	return Vector2f(y, -x);
}

float determinant(const Vector2f& a, const Vector2f& b) {
	return a.x * b.y - a.y * b.x;
}

Vector2f& Vector2f::operator=(const Vector2f& arg) {
	this->x = arg.x;
	this->y = arg.y;
	return *this;
}

Vector2f& Vector2f::operator+=(const Vector2f& arg) {
	this->x += arg.x;
	this->y += arg.y;
	return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& arg) {
	this->x -= arg.x;
	this->y -= arg.y;
	return *this;
}

Vector2f& Vector2f::operator*=(const Vector2f& arg) {
	this->x *= arg.x;
	this->y *= arg.y;
	return *this;
}

Vector2f& Vector2f::operator=(const float arg) {
	this->x = arg;
	this->y = arg;
	return *this;
}

Vector2f& Vector2f::operator+=(const float arg) {
	this->x += arg;
	this->y += arg;
	return *this;
}

Vector2f& Vector2f::operator-=(const float arg) {
	this->x -= arg;
	this->y -= arg;
	return *this;
}

Vector2f& Vector2f::operator*=(const float arg) {

	this->x *= arg;
	this->y *= arg;
	return *this;
}

Vector2f Vector2f::operator*(const Vector2f& arg) {
	Vector2f V = Vector2f(this->x * arg.x, this->y * arg.y);
	return V;
}

Vector2f Vector2f::operator+(const Vector2f& arg) {
	Vector2f V = Vector2f(this->x + arg.x, this->y + arg.y);
	return V;
}

Vector2f Vector2f::operator-(const Vector2f& arg) {
	Vector2f V = Vector2f(this->x - arg.x, this->y - arg.y);
	return V;
}

Vector2f Vector2f::operator*(const float arg) {
	Vector2f V = Vector2f(this->x * arg, this->y * arg);
	return V;
}

Vector2f Vector2f::operator/(const float arg) {
	Vector2f V = Vector2f(this->x / arg, this->y / arg);
	return V;
}

Vector2f Vector2f::operator+(const float arg) {
	Vector2f V = Vector2f(this->x + arg, this->y + arg);
	return V;
}

Vector2f Vector2f::operator-(const float arg) {
	Vector2f V = Vector2f(this->x - arg, this->y - arg);
	return V;
}

Vector2f Vector2f::operator-() {
	Vector2f V = Vector2f(-this->x, -this->y);
	return V;
}

