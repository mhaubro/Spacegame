/*
 * EnemyManager.cpp
 *
 *  Created on: 10/06/2016
 *      Author: Martin
 */

#include "EnemyManager.h"

EnemyManager::EnemyManager() : enemy_number(3) {
	LinkedEntityList enemies;
}

EnemyManager::~EnemyManager() {
	//Only delete if a new is done. No new.
}

void EnemyManager::update(){
	enemies.updateAll();
	enemies.removeDead();

	if (enemies.size() < enemy_number+1){
		squareEnemy * e = new squareEnemy();
		enemies.add(e);
	}
}
void EnemyManager::render(){
	enemies.renderAll();
}

unsigned int EnemyManager::size(){
	return enemies.size();
}
