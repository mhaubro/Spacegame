//Author: MG

#ifndef SRC_MATH_VECTOR2F_H_
#define SRC_MATH_VECTOR2F_H_

class Vector2f {
public:
	float x,y;
	Vector2f();
	Vector2f(float x, float y);
	Vector2f(const Vector2f & v);
	Vector2f(Vector2f & v);
	virtual ~Vector2f();

	float length();
	float angle();
	float dotProduct(Vector2f extv);
	float crossproduct(Vector2f arg);
	Vector2f projectAt(Vector2f arg);
	float scalarProjectAt(Vector2f arg);

	Vector2f vertexTransformed(Vector2f positionTransform, float rotationTransform);

	void wrap(Vector2f min, Vector2f max);
	Vector2f normalized();
	Vector2f leftNormal();
	Vector2f rightNormal();

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
	Vector2f operator/(const float arg);
	Vector2f operator+(const float arg);
	Vector2f operator-(const float arg);

	Vector2f operator-();



};
//extern Vector2f Transform(const Vector2f& offset, const Vector2f EntityPosition, float angle);//Bad name?

Vector2f FromAngle(float length, float angle);

float determinant(const Vector2f& a, const Vector2f& b);

#endif /* SRC_MATH_VECTOR2F_H_ */
