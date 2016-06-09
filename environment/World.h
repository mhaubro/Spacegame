/*
 * World.h
 *
 *  Created on: Apr 18, 2016
 *      Author: mathi
 */

#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include "Chunk.h"

#define WORLD_SIZE 64
#define CHUNKS_FROM_CENTER 2
#define NUMBER_OF_CHUNKS_LOADED (1 + CHUNKS_FROM_CENTER*2)

class World {
protected:

	Chunk ** chunks;
	void decrementIndex();
	void incrementIndex();

public:
	World();
	virtual ~World();

	void update(float x);
	void render();

	void checkBullets();
	void renderBullets();
	void removeBullets();

	float getHeight(float x);
	Vector2f& getNormal(float x, Vector2f &vec);
};

extern World world;

#endif /* SRC_WORLD_H_ */
