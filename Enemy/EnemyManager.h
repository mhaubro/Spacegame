//Author: MG

#ifndef SRC_ENEMY_ENEMYMANAGER_H_
#define SRC_ENEMY_ENEMYMANAGER_H_

#include "Enemy.h"
//#include "SquareEnemy.h"
//#include "RoundEnemy.h"
#include "LinkedList.h"
#include "Bullet.h"

class EnemyManager {

protected:

	class EnemyList: public LinkedList<Enemy> {
	public:
		EnemyList();
		virtual ~EnemyList();

		virtual void updateAll();
		virtual void renderAll();
		virtual bool firstInternalCollisionForTheRest(Node* current, Enemy* collided);
		virtual bool checkBulletCollision(Bullet* bullet);
		virtual bool shouldRemove(Node* node);
	};
	EnemyList enemies;
	unsigned int enemy_number;
	Vector2f generatePosition();

public:

	EnemyManager();
	virtual ~EnemyManager();

	virtual void update();
	virtual void render();
	int size();

	bool checkBulletCollision(Bullet * _bullet){
		return enemies.checkBulletCollision(_bullet);
	}
};

#endif /* SRC_ENEMY_ENEMYMANAGER_H_ */
