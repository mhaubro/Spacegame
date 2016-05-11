/*
 * Mathmatics.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: mathi
 */

#include "Mathematics.h"

float clamp(float x, float min, float max) {
	if (x < min)
		return min;
	if (x > max)
		return max;
	return x;
}

bool Equals(float a, float b, float tolerance){
	return a <= b + tolerance && a >= b - tolerance;
}

