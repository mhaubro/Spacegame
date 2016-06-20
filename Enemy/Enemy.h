/*
 * Enemy.h
 *
 *  Created on: 20/06/2016
 *      Author: Martin
 */

#ifndef SRC_ENEMY_ENEMY_H_
#define SRC_ENEMY_ENEMY_H_

#include "Entity.h"
#include "RigidBody.h"
#include "Polygon.h"
#include "Behavior.h"
#include "Vector2f.h"

class Enemy: public Entity, public RigidBody {
private:
	float health;
	void kill();

protected:
	Behavior * behavior;
	Polygon * collisionBox;

	bool enemyOnScreen();

	virtual void onDeath();
	void applyDamage(float damage);

	virtual void makeDesicion();
public:

	Enemy(float _health, Polygon * _collisionBox, Behavior * _behavior,
			Vector2f _position, float mass = 1, float inertia = .5,
			float angle = 0, Vector2f Velocity = Vector2f(0, 0));
	virtual ~Enemy();
	void update();
	void render();

	Polygon * getPolygon();

	Vector2f targetAngle;//TODO Remove;

};

#endif /* SRC_ENEMY_ENEMY_H_ */
