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

float Vector2f::length() {
	return sqrtf((x * x) + (y * y));
}

float Vector2f::angle() {
	if (x == 0 && y == 0)
		return 0;
	return atan2f(x, y);
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

Vector2f& Vector2f::operator*=(const float arg) {

	this->x *= arg;
	this->y *= arg;
	return *this;
}
