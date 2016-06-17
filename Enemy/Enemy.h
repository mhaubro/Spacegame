//Author: MH

#ifndef SRC_ENEMY_ENEMY_H_
#define SRC_ENEMY_ENEMY_H_

#define FIRERATE (float) 1.5
#include "Entity.h"
#include "RigidBody.h"
#include "Polygon.h"
#include "myassets.h"
#include "bullet.h"
#include "random.h"
#include "Sprite.h"
#include "Animation.h"

//TODO CLEAN UP IN METHODS AS WELL AS MEMBER-VALUES.
class Enemy : public Entity, public RigidBody{
protected:

	Sprite sprite;
	Animation exhaust;

	int height;
	int health;
	int enemyValue;

	Polygon * collisionBox;

	Vector2f shotOffset;//Marks offset from center of object to shooting mound. Both positive as well as negativ//TODO Maybe delete? - Or make float?
	Vector2f aimVector;

	double lastShot = 0;

	bool braking;
	bool aiming;
	bool shooting;

	float maxV;//Sets the units max velocity in units.

	float angle;
	float birthTime;
	float brakeStart;
	float aimStart;
	float shotStart;
	float shotAngle;
	float brakeTime;//D
	float aimTime;
	float shotDT;
	float shotTime;//Sends out bullets every shotDT in a time of shotTime (DT = .2 & time = .3 -> 2 shots with .2 sec between).

	Vector2f getShortestDiffVector(Vector2f v1, Vector2f v2);
	Vector2f getShotVel(float velocity, float angle);

	float getHeight();

	bool enemyOnScreen();

	void checkBounds();//Checks if the enemy is more than 1.6 chunk-length away. If yes, it's killed.
	void shoot();
	void aim();
	void turn();
	void brake();
	void hitBrake();
	void aimAction();
	void enemyShot();
	void updatePh();
	void checkAlive();
	void shotAction(float angle);
	void bestMove();
	void updatePosition();
	void checkCollision();

	virtual Vector2f getShotPos();
	virtual void moveAction(Vector2f vectorToPlayer);
	virtual float calcAngleToPlayer();
	virtual bool shotInRange(Vector2f shotVector);
	virtual bool checkShot(Vector2f VectorToPlayer);

public:

	Enemy(Polygon * collisionBox, Vector2f pos, Vector2f vel = Vector2f());

	Enemy& operator=(const Enemy & enemy);
	virtual ~Enemy();

	void update();
	void render();
	//int getPolySize();//USED FOR DEBUGGING
	bool checkHit(Bullet * _bullet);

	Polygon * getPolygon();
};

#endif /* SRC_ENEMY_ENEMY_H_ */
