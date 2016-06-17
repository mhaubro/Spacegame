//Author: MG

#ifndef SRC_PROCEDURAL_PERLINNOISE_H_
#define SRC_PROCEDURAL_PERLINNOISE_H_

#include "Octave.h"

class PerlinNoise {

protected:

public:
	PerlinNoise();
	virtual ~PerlinNoise();

	float noise(float x);

};

#endif /* SRC_PROCEDURAL_PERLINNOISE_H_ */
