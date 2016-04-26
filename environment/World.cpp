/*
 * World.cpp
 *
 *  Created on: Apr 18, 2016
 *      Author: mathi
 */

#include "World.h"
#include "Chunk.h"

#define NUMBER_OF_CHUNKS_LOADED 4

Chunk **chunks;

World::World() {
	chunks = new Chunk*[NUMBER_OF_CHUNKS_LOADED];
	for (int i = 0; i < NUMBER_OF_CHUNKS_LOADED; ++i) {
		chunks[i] = new Chunk(i);
	}
}

World::~World() {
	for (int i = 0; i < NUMBER_OF_CHUNKS_LOADED; ++i) {
		delete chunks[i];
	}
	delete[] chunks;
}

void World::render(){
	for (int var = 0; var < NUMBER_OF_CHUNKS_LOADED; ++var) {
		chunks[var]->render();
	}
}

float World::getHeight(float x){

	int i = ((int)(x/CHUNK_SIZE))%NUMBER_OF_CHUNKS_LOADED;

	return chunks[i]->getHeight((x-i*CHUNK_SIZE));
}

