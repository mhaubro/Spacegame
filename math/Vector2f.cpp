/*
 * Vector2f.cpp
 *
 *  Created on: Apr 19, 2016
 *      Author: mathi
 */

#include "Vector2f.h"
#include "math.h"

Vector2f::Vector2f() :
		x(0), y(0) {
}

Vector2f::Vector2f(float x, float y) :
		x(x), y(y) {
}

Vector2f::~Vector2f() {
}

Vector2f FromAngle(float length, float angle) {
	return Vector2f(length * cosf(angle), -(length * sinf(angle)));
}
float Vector2f::dotProduct(Vector2f extv) {
	return x * extv.x + y * extv.y;
}

float Vector2f::length() {
	return sqrtf((x * x) + (y * y));
}

float Vector2f::angle() {
	if (x == 0 && y == 0)
		return 0;
	return atan2f(x, y);
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
	float length = this->length();
	return Vector2f(x / length, y / length);
}

Vector2f Vector2f::LeftNormal(const Vector2f& arg) {
	return Vector2f(-arg.y,arg.x);
}

Vector2f Vector2f::RightNormal(const Vector2f& arg) {
	return Vector2f(arg.y,-arg.x);
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

Vector2f Vector2f::operator+(const float arg) {
	Vector2f V = Vector2f(this->x + arg, this->y + arg);
	return V;
}

Vector2f Vector2f::operator-(const float arg) {
	Vector2f V = Vector2f(this->x - arg, this->y - arg);
	return V;
}

