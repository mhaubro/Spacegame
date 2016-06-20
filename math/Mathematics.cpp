//Author: MH

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

float loop(float val, float min, float max){
	if (min > max){
		return -1;
	}
	while (val > max){
		val -= (max - min);
	}
	while (val < min){
		val += (max - min);
	}
	return val;
}

