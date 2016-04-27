/*
 * Chunk.h
 *
 *  Created on: Apr 18, 2016
 *      Author: mathi
 */

#ifndef SRC_ENVIRONMENT_CHUNK_H_
#define SRC_ENVIRONMENT_CHUNK_H_

#include "Vector2f.h"

#define CHUNK_SIZE 16
#define VERTEX_PER_UNIT 2
#define VERTEX_NUMBER (CHUNK_SIZE * VERTEX_PER_UNIT + 1)
#define VERTEX_SEPERATION (((float) 1) / VERTEX_PER_UNIT)

class Chunk {
protected:

	int index;
	float heightMap[VERTEX_NUMBER];

public:
	Chunk(int _index);
	virtual ~Chunk();
	void render();
	void rewrite(int index);

	float getHeight(float x);
	Vector2f& getNormal(float x, Vector2f &vec);

};

#endif /* SRC_ENVIRONMENT_CHUNK_H_ */
