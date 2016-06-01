#ifndef BULLET_H_
#define BULLET_H_

#include<vector>

#include "game.h"
#include "PhysicsConstants.h"
#include "GD2.h"
#include "particle.h"


class bullet{
private:
	void applydrag(int dt);
	void applyG(int dt);

public:

	Vector2f position;
	Vector2f velocity;
	int radius;
	unsigned int color;
	bool visible;

	bullet(Vector2f& position, Vector2f& velocity, int radius, int color);
	void update();
	void applyforces(int dt);
	void render();
	void turnInvisible();
	bool checkEarthCollision();
	bool isVisible();
	bool outOfBounds();

	void operator= (const bullet& b);
};

extern std::vector<bullet> friendlybullets;
extern std::vector<bullet> foebullets;


#endif
