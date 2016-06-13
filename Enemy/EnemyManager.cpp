/*
 * EnemyManager.cpp
 *
 *  Created on: 10/06/2016
 *      Author: Martin
 */

#include "EnemyManager.h"

EnemyManager::EnemyManager() : enemy_number(3) {
	std::vector<squareEnemy *> enemies;
}

EnemyManager::~EnemyManager() {
	//Only delete if a new is done. No new.
}

bool isEnemyDead(squareEnemy * e){//NOTE: MUST BE DEFINED BEFORE REMOVEENEMIES OR IN THE TOP OF THE .CPP-file. Predicate-function.
	if (e->isDead()){
		delete e;
		return true;
	}
	return false;
}

void EnemyManager::update(){
	for (std::vector<squareEnemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i){
		(*i)->update();
	}
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), isEnemyDead),enemies.end());

	if (enemies.size() < enemy_number+1){
		squareEnemy * e = new squareEnemy();
		enemies.push_back(e);
	}
}
void EnemyManager::render(){
	for (std::vector<squareEnemy *>::iterator i = enemies.begin(); i != enemies.end(); ++i){
		(*i)->render();
	}
}

unsigned int EnemyManager::size(){
	return enemies.size();
}

//void EnemyManager::addEnemy(Enemy * enemy){
//	enemies.push_back(enemy);
//}

