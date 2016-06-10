/*
 * World.cpp
 *
 *  Created on: Apr 18, 2016
 *      Author: mathi
 */
#include <vector>
#include "World.h"
#include "GD2.h"
#include "myassets.h"
#include "bullet.h"

#include "GraphicsTemplates.h"
#include "Animation.h"
#include "StaticAnimationEffect.h"

World world;

World::World() {
	chunks = new Chunk*[NUMBER_OF_CHUNKS_LOADED];
	for (int i = 0; i < NUMBER_OF_CHUNKS_LOADED; ++i) {
		chunks[i] = new Chunk(i - CHUNKS_FROM_CENTER);
	}
}

World::~World() {
	for (int i = 0; i < NUMBER_OF_CHUNKS_LOADED; ++i) {
		delete chunks[i];
	}
	delete[] chunks;
}

void World::update(float x) {
	for (int i = 0; i < NUMBER_OF_CHUNKS_LOADED; i++) {
		chunks[i]->update(x);
	}
}

void World::render() {
	GD.SaveContext();
	GD.RestoreContext();

	for (int var = 0; var < NUMBER_OF_CHUNKS_LOADED; ++var) {
		chunks[var]->render();
	}
}

float World::getHeight(float x) {
	int index = ((int) (x / CHUNK_SIZE));
	for (int i = 0; i < NUMBER_OF_CHUNKS_LOADED; i++) {
		if (chunks[i]->getIndex() == index) {
			return chunks[i]->getHeight((x - index * CHUNK_SIZE));
		}
	}
	return 0;
}

Vector2f& World::getNormal(float x, Vector2f &vec) {
	int index = ((int) (x / CHUNK_SIZE));
	for (int i = 0; i < NUMBER_OF_CHUNKS_LOADED; i++) {
		if (chunks[i]->getIndex() == index) {
			return chunks[i]->getNormal((x - index * CHUNK_SIZE), vec);
		}
	}
	return vec = Vector2f(0, 1);
}

