/*
 * PerlinNoise.cpp
 *
 *  Created on: Apr 25, 2016
 *      Author: mathi
 */

#include "PerlinNoise.h"

#define F1  ((float)5)
#define F2  ((float)4)
#define F4  ((float)3)
#define F8  ((float)2)
#define F16  ((float)1)

#define AMP ((float)10)
#define FACTOR ((float)(AMP/(F1 + F2 + F4 + F8 + F16)))

PerlinNoise::PerlinNoise(){

}

PerlinNoise::~PerlinNoise() {
	// TODO Auto-generated destructor stub
}

float PerlinNoise::noise(float x) {
	static Octave octave1 = Octave(1, 42);
	static Octave octave2 = Octave(2, 42);
	static Octave octave4 = Octave(4, 42);
	static Octave octave8 = Octave(8, 42);
	static Octave octave16 = Octave(16, 42);

	return (F16 * octave16.interpolate(x) + F8 * octave8.interpolate(x)
			+ F4 * octave4.interpolate(x) + F2 * octave2.interpolate(x)
			+ F1 * octave1.interpolate(x)) * FACTOR ;
}

