#ifndef BULLET_H_
#define BULLET_H_

#include<vector>

#include "PhysicsConstants.h"
#include "PhysicsObject.h"
#include "GD2.h"
#include "Animation.h"

#define BULLET_MASS .02

#define Lifespan 10

class Bullet: public PhysicsObject {
private:

	const double startTime;//Make non-const? - Depends on vector of bullets or bullet *
	bool mDead;
	bool mFriendly;
	float mRadius;
	Animation mAnimation;

	bool checkEarthCollision();

public:

	bool outOfBounds();

	Bullet& operator=(const Bullet& b);

	Bullet(Vector2f& position, Vector2f& velocity, float radius, bool friendly);
	void update();
	void render();

	bool isDead();
	void kill();


	bool getFriendly();
	float getRadius();

	//void operator=(const Bullet& b);//TODO Probably delete this line
};

#endif
