/*
 * Enemy.h
 *
 *  Created on: 06/06/2016
 *      Author: Martin
 */

#ifndef SRC_ENEMY_ENEMY_H_
#define SRC_ENEMY_ENEMY_H_

#define FIRERATE (float) 1.5
#include <vector>
#include <memory>//USE SMART POINTERS FOR ENEMY-ARRAY INSTEAD OF CLASSICAL//TODO
#include "Entity.h"
#include "graphics.h"
#include "Sprite.h"
#include "Animation.h"
#include "Polygon.h"
#include "myassets.h"
#include "bullet.h"
#include "random.h"

class Enemy : public Entity, public PhysicsObject{
protected:
	int height;

	Sprite* sprite;
	Sprite* exhaust;
	Animation* anim;
	Polygon* collisionBox;

	Vector2f shotOffset = Vector2f(.5, 0);//Marks offset from center of object to shooting mound. Both positive as well as negativ
	int health;
	float birthTime;
	bool orientRight = true;//Boolean value that marks if the enemy is oriented toward right. If false, it is oriented towards the left.
	bool braking = false;
	float brakeStart;
	float brakeTime = 1;
	bool aiming;
	float aimStart;
	float aimTime = 1.75;
	bool shooting;
	float shotStart;
	float shotAngle;
	float lastShot = 0;
	float shotDT = .2;
	float shotTime = .3;

	void checkHits();
	void bestMove();
	void updatePosition();

	float calcAngleToPlayer();
	void enemyShot(float angle);
	Vector2f getShotPos();
	Vector2f getShotVel(float velocity, float angle);
	void checkAlive();
	void kill();
	bool shotInRange(Vector2f shotVector);
	void shotAction(float angle);
	void moveAction(Vector2f vectorToPlayer);
	float getHeight();
	void turn();
	void brakeAction();
	void brake();
	void shotAction();
	void updatePh();
	bool enemyOnScreen();


public:

	bool isDead;//TODO move to private, make functions kill and read.


	Enemy(Vector2f pos, Vector2f vel);
	Enemy& operator=(const Enemy & enemy);
	virtual ~Enemy();

	void update();
	void render();
	bool collide(Entity entity);
};
extern std::vector<Enemy*> enemies;
#endif /* SRC_ENEMY_ENEMY_H_ */
