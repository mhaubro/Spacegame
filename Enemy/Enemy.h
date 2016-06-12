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
#include "PhysicsObject.h"
#include "SpriteTemplate.h"
#include "AnimationTemplate.h"
#include "Polygon.h"
#include "myassets.h"
#include "bullet.h"
#include "random.h"

class Enemy : public Entity, public PhysicsObject{
protected:

	int height;
	SpriteTemplate* sprite;
	SpriteTemplate* exhaust;
	AnimationTemplate* anim;

	double lastShot = 0;

	Polygon* collisionBox;
	float angle;

	Vector2f shotOffset = Vector2f(.5, 0);//Marks offset from center of object to shooting mound. Both positive as well as negativ
	Vector2f aimVector;
	int health;
	float birthTime;
	bool orientRight;//Boolean value that marks if the enemy is oriented toward right. If false, it is oriented towards the left.
	bool braking;
	float brakeStart;
	float brakeTime = 1;
	bool aiming;
	float aimStart;
	float aimTime = 1.75;
	bool shooting;
	float shotStart;
	float shotAngle;
	float shotDT = .2;
	float shotTime = .3;//Sends out bullets every shotDT in a time of shotTime (DT = .2 & time = .3 -> 2 shots with .2 sec between).



	Vector2f generatePosition();//TODO CLEAN AS WELL AS GIVE BETTER METHOD NAMES
	Vector2f getShortestDiffVector(Vector2f v1, Vector2f v2);
	Vector2f getShotPos();
	Vector2f getShotVel(float velocity, float angle);

	float calcAngleToPlayer();
	float getHeight();

	bool checkShot(Vector2f VectorToPlayer);
	bool enemyOnScreen();
	bool shotInRange(Vector2f shotVector);

	void checkBounds();
	void shoot();
	void aim();
	void turn();
	void brakeAction();
	void brake();
	void aimAction();
	void enemyShot();
	void updatePh();
	void checkAlive();
	void shotAction(float angle);
	void moveAction(Vector2f vectorToPlayer);
	void checkHits();
	void bestMove();
	void updatePosition();



public:

	Enemy(Vector2f pos, Vector2f vel);
	Enemy();

	Enemy& operator=(const Enemy & enemy);
	virtual ~Enemy();

	void update();
	void render();
	bool collide(Entity entity);//TODO Maybe delete.
};

#endif /* SRC_ENEMY_ENEMY_H_ */
