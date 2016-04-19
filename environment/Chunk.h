/*
 * Chunk.h
 *
 *  Created on: Apr 18, 2016
 *      Author: mathi
 */

#ifndef SRC_ENVIRONMENT_CHUNK_H_
#define SRC_ENVIRONMENT_CHUNK_H_

#define CHUNK_SIZE 64

class Chunk {
protected:

	short index;
	short heightMap [CHUNK_SIZE];

public:
	Chunk(short _index);
	virtual ~Chunk();
	void render();

};

#endif /* SRC_ENVIRONMENT_CHUNK_H_ */
