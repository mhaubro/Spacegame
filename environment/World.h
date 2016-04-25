/*
 * World.h
 *
 *  Created on: Apr 18, 2016
 *      Author: mathi
 */

#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include "Chunk.h"

#define WORLD_SIZE 16

class World {
protected:

public:
	World();
	virtual ~World();

	void render();
};

#endif /* SRC_WORLD_H_ */
