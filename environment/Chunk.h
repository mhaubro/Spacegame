/*
 * Chunk.h
 *
 *  Created on: Apr 18, 2016
 *      Author: mathi
 */

#ifndef SRC_ENVIRONMENT_CHUNK_H_
#define SRC_ENVIRONMENT_CHUNK_H_

#include "Vector2f.h"
#include "Random.h"

#define CHUNK_SIZE 16
#define VERTEX_PER_UNIT 2
#define VERTEX_NUMBER (CHUNK_SIZE * VERTEX_PER_UNIT + 1)
#define VERTEX_SEPERATION (((float) 1) / VERTEX_PER_UNIT)

#define NUM_DETAILS 5

class Chunk {
protected:

	struct Detail {
		char handle, cell;
		float x, y;

		Detail() :
				handle(0), cell(0), x(0), y(0) {
		}
		;
	};

//	Detail details[NUM_DETAILS];

	int index;
	float heightMap[VERTEX_NUMBER];

public:
	Chunk(int _index);
	virtual ~Chunk();
	void render();
	void update(float x);
	void rewrite(int index);

	float getHeight(float x);
	Vector2f& getNormal(float x, Vector2f &vec);
	int getIndex();

};

#endif /* SRC_ENVIRONMENT_CHUNK_H_ */
