/*
 * Octave.cpp
 *
 *  Created on: Apr 25, 2016
 *      Author: mathi
 */

#include "Octave.h"

Octave::Octave(int f, int seed) :
		f(f), seed(seed) {
	// TODO Auto-generated constructor stub

}

Octave::~Octave() {
	// TODO Auto-generated destructor stub
}

float Octave::interpolate(float x) {

	int x1 = (int)x / ((float)CHUNK_SIZE / f);
	float a = x1 * ((float)CHUNK_SIZE / f);
	float b = (x1+1) * ((float)CHUNK_SIZE / f);

	float y1 = randomFloat(x1);
	float y2 = randomFloat(x1+1);

	float v = (x-a) / (b-a);
	v = (v*v*(3-2*v));

	return (y2*v)+(y1*(1-v));
}

float Octave::randomFloat(int x) {
	static short v1[] = { 5, 2, 8, 2, 1, 9, 6, 3, 9, 1, 3, 8, 4, 2, 8, 5, 9, 3,
			5, 4 };
	static short v2[] = { 12, 5, 0, 2, 7, 9 };
	int y = (x >> 1) ^ (-(x & 1u) & 0xB400u);
	return ((float) 1) / v1[(y + (v2[v1[x] % 6])) % 20];
}

