/*
 * EnemyManager.h
 *
 *  Created on: 10/06/2016
 *      Author: Martin
 */

#ifndef SRC_ENEMY_ENEMYMANAGER_H_
#define SRC_ENEMY_ENEMYMANAGER_H_

#include <vector>
#include <algorithm>
#include "Enemy.h"

class EnemyManager {

protected:
	std::vector<Enemy *> enemies;
	unsigned int enemy_number;

public:
	EnemyManager();
	unsigned int size();
	virtual ~EnemyManager();
	virtual void update();
	virtual void render();
	virtual void addEnemy(Enemy * enemy);
};

#endif /* SRC_ENEMY_ENEMYMANAGER_H_ */
