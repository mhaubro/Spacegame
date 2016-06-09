#ifndef BULLET_H_
#define BULLET_H_

#include<vector>

#include "game.h"
#include "PhysicsConstants.h"
#include "PhysicsObject.h"
#include "Animation.h"

#define Lifespan 5

class bullet : public PhysicsObject{
private:

	double startTime;
	bool dead = false;
	Animation anim;

public:

	float radius;
	unsigned int color;


	bullet& operator=(const bullet& b);

	bullet(Vector2f& position, Vector2f& velocity, float radius, int color);
	void update();
	void render();

	bool checkEarthCollision();

	bool isDead();
	void kill();
};

extern std::vector<bullet> friendlybullets;
extern std::vector<bullet> foebullets;


#endif
