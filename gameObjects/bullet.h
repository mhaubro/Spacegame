#ifndef BULLET_H_
#define BULLET_H_

#include<vector>

#include "game.h"
#include "PhysicsConstants.h"
#include "PhysicsObject.h"
#include "GD2.h"
#include "particle.h"


#define Lifespan 10

class bullet : public PhysicsObject{
private:

	const double startTime;
	bool dead = false;
	Animation anim;

public:

	float radius;
	unsigned int color;

	bullet(Vector2f& position, Vector2f& velocity, float radius, int color);
	void update();
	void render();

	bool checkEarthCollision();

	bool isDead();
	void kill();

	void operator= (const bullet& b);
};

extern std::vector<bullet> friendlybullets;
extern std::vector<bullet> foebullets;


#endif
