/*
 * World.cpp
 *
 *  Created on: Apr 18, 2016
 *      Author: mathi
 */
#include <vector>
#include "World.h"
#include "Chunk.h"
#include "GD2.h"
#include "myassets.h"
#include "bullet.h"

#define CHUNKS_FROM_CENTER 1
#define NUMBER_OF_CHUNKS_LOADED (1 + CHUNKS_FROM_CENTER*2)

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
	checkBullets();
}

void World::render() {
	GD.SaveContext();
	GD.RestoreContext();

	for (int var = 0; var < NUMBER_OF_CHUNKS_LOADED; ++var) {
		chunks[var]->render();
	}

	//Renders bullets
	renderBullets();
}

//OBS: Bullet collisions with players/enemies/targets are handled by those objects.
void World::checkBullets(){
	for(std::vector<bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
	    bullet & b = *it;
	    b.applyforces(timer.getDeltaTime());
	    if(b.checkEarthCollision() || b.outOfBounds()){
	    	b.turnInvisible();

	    }
    	b.update();

	}
	removeBullets();
}

void World::removeBullets(){
	std::vector<bullet>::iterator i = bullets.begin();
	while (i != bullets.end()){
		bullet & b = *i;
		if (!b.isVisible()){//If a bullet is to be deleted, it is swapped with the last element, which is then deleted, since order doesn't matter
			b = bullets[bullets.size()-1];
			bullets.erase(bullets.end());
		} else {
			++i;
		}


	}
}

void World::renderBullets(){
	for(std::vector<bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
		bullet & b = *it;
		b.render();
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

