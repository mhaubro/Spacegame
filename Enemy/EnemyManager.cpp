/*
 * EnemyManager.cpp
 *
 *  Created on: 10/06/2016
 *      Author: Martin
 */

#include "EnemyManager.h"

EnemyManager::EnemyManager() :
		enemies(), enemy_number(3) {
}

EnemyManager::~EnemyManager() {
	//Only delete if a new is done. No new.
}

void EnemyManager::update() {
	enemies.updateAll();
	enemies.clean();

	if (enemies.size() < enemy_number + 1) {
		squareEnemy * e = new squareEnemy();
		enemies.add(e);
	}
}
void EnemyManager::render() {
	enemies.renderAll();
}

int EnemyManager::size() {
	return enemies.size();
}

EnemyManager::EnemyList::EnemyList() :
LinkedList<Enemy>() {
}
EnemyManager::EnemyList::~EnemyList() {
}

bool EnemyManager::EnemyList::shouldRemove(Node* node){
	return node->mData->isDead();
}

void EnemyManager::EnemyList::updateAll() {
	Node* tmp = mHead;
	while (tmp) {
		tmp->mData->update();
		tmp = tmp->mNext;
	}
}
void EnemyManager::EnemyList::renderAll() {
	Node* tmp = mHead;
	while (tmp) {
		tmp->mData->render();
		tmp = tmp->mNext;
	}
}

bool EnemyManager::EnemyList::firstInternalCollisionForTheRest(Node* current, Enemy* collided) {
	Node* tmp = current->mNext;
	while (tmp) {
		tmp = tmp->mNext;
	}
}

void EnemyManager::EnemyList::checkBulletCollision(Bullet* bullet) {
	Node* tmp = mHead;
	while (tmp) {
		if (tmp->mData->checkHit(bullet)) {
			return;
		}
		tmp = tmp->mNext;
	}
}
