/*
 * Vector2f.h
 *
 *  Created on: Apr 19, 2016
 *      Author: mathi
 */

#ifndef SRC_MATH_VECTOR2F_H_
#define SRC_MATH_VECTOR2F_H_

class Vector2f {
public:
	float x,y;
	Vector2f();
	Vector2f(float x, float y);
	virtual ~Vector2f();

	float length();
	float angle();
	float dotProduct(Vector2f extv);

	Vector2f& operator=(const Vector2f& arg);
	Vector2f& operator+=(const Vector2f& arg);
	Vector2f& operator-=(const Vector2f& arg);
	Vector2f& operator*=(const Vector2f& arg);

	Vector2f& operator+=(const float arg);
	Vector2f& operator-=(const float arg);
	Vector2f& operator*=(const float arg);

	Vector2f operator*(const Vector2f& arg);
	Vector2f operator+(const Vector2f& arg);
	Vector2f operator-(const Vector2f& arg);
	Vector2f operator*(const float arg);
	Vector2f operator+(const float arg);
	Vector2f operator-(const float arg);



};

extern Vector2f FromAngle(float length, float angle);

#endif /* SRC_MATH_VECTOR2F_H_ */
