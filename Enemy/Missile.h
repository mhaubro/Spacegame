/*
 * Missile.h
 *
 *  Created on: 20/06/2016
 *      Author: Martin
 */

#ifndef SRC_ENEMY_MISSILE_H_
#define SRC_ENEMY_MISSILE_H_

#include "Vector2f.h"
#include "Sprite.h"
#include "Animation.h"
#include "Enemy.h"

class Missile : public Enemy{
protected:
	Sprite sprite;
	Animation exhaust;

public:
	Missile(Vector2f _position, Vector2f _velocity);
	virtual ~Missile();

	void render();


};

#endif /* SRC_ENEMY_MISSILE_H_ */
