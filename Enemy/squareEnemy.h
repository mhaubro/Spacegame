/*
 * squareEnemy.h
 *
 *  Created on: 12/06/2016
 *      Author: Martin
 */

#ifndef SRC_ENEMY_SQUAREENEMY_H_
#define SRC_ENEMY_SQUAREENEMY_H_

#include "Vector2f.h"
#include "Enemy.h"

class squareEnemy : public Enemy {
protected:

	bool orientRight;

	bool shotInRange(Vector2f shotVector);
	float calcAngleToPlayer();
	Vector2f getShotPos();
	bool checkShot(Vector2f VectorToPlayer);
	void turn();//Turns the orientation of the enemy ship
	void moveAction(Vector2f vectorToPlayer);//Maybe use defined vector as the ones in the top of the file.


public:
	squareEnemy(Vector2f _position, Vector2f _velocity = Vector2f());
	squareEnemy& operator=(const squareEnemy & squareenemy);
	virtual ~squareEnemy();
};

#endif /* SRC_ENEMY_SQUAREENEMY_H_ */
