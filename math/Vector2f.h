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

	void wrap(Vector2f min, Vector2f max);
	Vector2f normalized();
	static Vector2f LeftNormal(const Vector2f& arg);
	static Vector2f RightNormal(const Vector2f& arg);

	Vector2f& operator=(const Vector2f& arg);
	Vector2f& operator+=(const Vector2f& arg);
	Vector2f& operator-=(const Vector2f& arg);
	Vector2f& operator*=(const Vector2f& arg);

	Vector2f& operator=(const float);
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
