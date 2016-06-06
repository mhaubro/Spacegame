/*
 * Octave.h
 *
 *  Created on: Apr 25, 2016
 *      Author: mathi
 */

#ifndef SRC_PROCEDURAL_OCTAVE_H_
#define SRC_PROCEDURAL_OCTAVE_H_

#include "Chunk.h"
#include "World.h"

class Octave {
protected:
	const int f; // points per chunk
	const int seed;
	const int size;
	float randomFloat(int x);

public:
	Octave(int f, int seed);
	virtual ~Octave();

	float interpolate(float x);
};

#endif /* SRC_PROCEDURAL_OCTAVE_H_ */
