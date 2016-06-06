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
void World::checkBullets() { //Should be made to one function called twice, but this demands inclusion of bullet in the header, which for some unknown reason triggers compiler-errors in player.h.
	//Friendly bullets
	for (std::vector<bullet>::iterator it = friendlybullets.begin();
			it != friendlybullets.end(); ++it) {
		bullet & b = *it;
		if (b.checkEarthCollision()) {
			b.kill();

		}
		b.update();

	}

	for (std::vector<bullet>::iterator it = foebullets.begin();
			it != foebullets.end(); ++it) {
		bullet & b = *it;
		if (b.checkEarthCollision()) {
			b.kill();

		}
		b.update();
	}
	removeBullets();
}

void World::removeBullets() {//See comment to update-bullets about double code.
	std::vector<bullet>::iterator i = friendlybullets.begin();
	while (i != friendlybullets.end()) {
		bullet & b = *i;
		if (b.isDead()) {//If a bullet is to be deleted, it is swapped with the last element, which is then deleted, since order doesn't matter
			b = friendlybullets[friendlybullets.size() - 1];
			friendlybullets.erase(friendlybullets.end());
		} else {
			++i;
		}

	}

	i = foebullets.begin();
	while (i != foebullets.end()) {
		bullet & b = *i;
		if (b.isDead()) {//If a bullet is to be deleted, it is swapped with the last element, which is then deleted, since order doesn't matter
			b = foebullets[foebullets.size() - 1];
			foebullets.erase(foebullets.end());
		} else {
			++i;
		}

	}
}

void World::renderBullets() {
	for (std::vector<bullet>::iterator it = friendlybullets.begin();
			it != friendlybullets.end(); ++it) {
		bullet & b = *it;
		b.render();
	}
	for (std::vector<bullet>::iterator it = foebullets.begin();
			it != foebullets.end(); ++it) {
		bullet & b = *it;
		b.render();
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
			return chunks[i]->getNormal((x - i * CHUNK_SIZE), vec);
		}
	}
	return vec = Vector2f(0,1);
}

