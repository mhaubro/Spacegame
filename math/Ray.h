//Author: MH

#ifndef SRC_MATH_RAY_H_
#define SRC_MATH_RAY_H_

#include "Vector2f.h"

class Ray {
public:
	Ray(Vector2f origin, Vector2f direction);
	virtual ~Ray();

	Vector2f origin;
	Vector2f direction;

	Vector2f getPoint(float t);

};

#endif /* SRC_MATH_RAY_H_ */
