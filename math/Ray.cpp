/*
 * Ray.cpp
 *
 *  Created on: May 11, 2016
 *      Author: mathi
 */

#include "Ray.h"

Ray::Ray(Vector2f origin, Vector2f direction)
:origin(origin), direction(direction.normalized())
{
}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}

Vector2f Ray::getPoint(float t){
// TODO
}

