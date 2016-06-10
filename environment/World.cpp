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
#include "graphics.h"

#include "GraphicsTemplates.h"
#include "Animation.h"
#include "StaticAnimationEffect.h"

World world;
bool isBDead(bullet b);

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
	GD.ColorA(255);
	GD.ColorRGB(WHITE);
	GD.Begin(BITMAPS);
	renderBullets();
}

//OBS: Bullet collisions with players/enemies/targets are handled by those objects.
void World::checkBullets() { //Should be made to one function called twice, but this demands inclusion of bullet in the header, which for some unknown reason triggers compiler-errors in player.h.
	//Friendly bullets
	Vector2f normal = Vector2f();
	for (std::vector<bullet>::iterator it = friendlybullets.begin();
			it != friendlybullets.end(); ++it) {
		bullet & b = *it;
		if (b.checkEarthCollision()) {
			world.getNormal(b.getPosition().x, normal);

			StaticAnimationEffect* effect = new StaticAnimationEffect(
					b.getPosition() + normal, .8, GroundCollisionAnimation32,
					normal.angle() + PI / 2, 1);
			game.mEffectManager.addEffect(effect);
			b.kill();
		} else if (b.outOfBounds()){
			b.kill();
		}
		b.update();
	}

	for (std::vector<bullet>::iterator it = foebullets.begin();
			it != foebullets.end(); ++it) {
		bullet & b = *it;
		if (b.checkEarthCollision()|| b.outOfBounds()) {
			b.kill();
		}
		b.update();
	}
	removeBullets();
}

void World::removeBullets() {//See comment to update-bullets about double code.
	friendlybullets.erase(std::remove_if(friendlybullets.begin(), friendlybullets.end(), isBDead), friendlybullets.end());
	foebullets.erase(std::remove_if(foebullets.begin(), foebullets.end(), isBDead), foebullets.end());
	//http://stackoverflow.com/questions/4115279/most-efficient-way-of-erasing-deleting-multiple-stdvector-elements-while-retai
}

bool isBDead(bullet b){
	return (b.isDead());
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
			return chunks[i]->getNormal((x - index * CHUNK_SIZE), vec);
		}
	}
	return vec = Vector2f(0, 1);
}

