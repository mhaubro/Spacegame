/*
 * Enemy.h
 *
 *  Created on: 06/06/2016
 *      Author: Martin
 */

#ifndef SRC_ENEMY_ENEMY_H_
#define SRC_ENEMY_ENEMY_H_

#define FIRERATE (float) 1.5

#include "Entity.h"
#include "SpriteTemplate.h"
#include "AnimationTemplate.h"
#include "Polygon.h"
#include "myassets.h"
#include "bullet.h"
#include "random.h"

class Enemy : public Entity, public PhysicsObject{
protected:
	int height;
	int health;
	double lastShot;

	SpriteTemplate* sprite;
	SpriteTemplate* exhaust;
	AnimationTemplate* anim;

	Polygon* collisionBox;

	Vector2f shotOffset;//Marks offset from center of object to shooting mound. Both positive as well as negativ

	bool orientRight;//Boolean value that marks if the enemy is oriented toward right. If false, it is oriented towards the left.

	void bestMove();
	void updatePosition();

	float calcAngleToPlayer();
	void enemyShot(float angle);
	Vector2f getShotPos();
	Vector2f getShotVel(float velocity, float angle);


public:

	Enemy(Vector2f pos, Vector2f vel);
	virtual ~Enemy();

	void update();
	void render();
	bool collide(Entity entity);
};
extern std::vector<Enemy> enemies;
#endif /* SRC_ENEMY_ENEMY_H_ */
