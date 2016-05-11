/*
 * Ray.h
 *
 *  Created on: May 11, 2016
 *      Author: mathi
 */

#ifndef SRC_MATH_RAY_H_
#define SRC_MATH_RAY_H_

#include "Vector2f.h"

class Ray {
public:
	Ray(Vector2f origin, Vector2f direction);
	virtual ~Ray();

	const Vector2f origin;
	const Vector2f direction;

	Vector2f getPoint(float t);

};

#endif /* SRC_MATH_RAY_H_ */
