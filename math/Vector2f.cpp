/*
 * Vector2f.cpp
 *
 *  Created on: Apr 19, 2016
 *      Author: mathi
 */

#include "Vector2f.h"
#include "Math.h"

Vector2f::Vector2f()
: x(0), y(0)
{}

Vector2f::Vector2f(float x, float y)
: x(x), y(y)
{}

Vector2f::~Vector2f() {
}

float Vector2f::length()
{
	return sqrtf((x*x)+(y*y));
}

float Vector2f::angle()
{
	if (x == 0 && y == 0)
		return 0;
	return atan2f(x,y);
}

Vector2f& Vector2f::operator=(const Vector2f& arg)
{
	this->x = arg.x;
	this->y = arg.y;
	return *this;
}

Vector2f& Vector2f::operator+(const Vector2f& v){

}

Vector2f& Vector2f::operator-(const Vector2f& v){

}

Vector2f& Vector2f::operator+=(const Vector2f& v){

}

Vector2f& Vector2f::operator-=(const Vector2f& v){

}

Vector2f& Vector2f::operator*(const float a){

}

Vector2f& Vector2f::operator/(const float a){

}

Vector2f& Vector2f::operator*=(const float a){

}

Vector2f& Vector2f::operator/=(const float a){

}
