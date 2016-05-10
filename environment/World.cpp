/*
 * World.cpp
 *
 *  Created on: Apr 18, 2016
 *      Author: mathi
 */

#include "World.h"
#include "Chunk.h"
#include "GD2.h"
#include "myassets.h"

#define CHUNKS_FROM_CENTER 1
#define NUMBER_OF_CHUNKS_LOADED (1 + CHUNKS_FROM_CENTER*2)
//#define world World
World world;

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

void World::update(float x) {

}

void World::render() {
	GD.SaveContext();
	GD.RestoreContext();

	for (int var = 0; var < NUMBER_OF_CHUNKS_LOADED; ++var) {
		chunks[var]->render();
	}
}

float World::getHeight(float x) {
	int i = ((int) (x / CHUNK_SIZE)) % NUMBER_OF_CHUNKS_LOADED;
	return chunks[i]->getHeight((x - i * CHUNK_SIZE));
}

Vector2f& World::getNormal(float x, Vector2f &vec) {
	int i = ((int) (x / CHUNK_SIZE)) % NUMBER_OF_CHUNKS_LOADED;
	return chunks[i]->getNormal((x - i * CHUNK_SIZE),vec);
}

void World::incrementIndex() {
	index = ((index + 1) % WORLD_SIZE);
}

void World::decrementIndex() {
	index = ((index - 1) % WORLD_SIZE);
}

