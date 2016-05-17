#ifndef BULLET_H
#define BULLET_H 1

#include "Vector2f.h"
#include "PhysicsConstants.h"
#include "GD2.h"
#include "graphics.h"

class particle{

private:
	void applydrag(int dt);
	void applyG(int dt);
	PhysicsObject ph;

public:
	Vector2f position;
	Vector2f velocity;
	bool visible;//Maybe useless. Rename to collided?? Maybe useful for bullets that's disappeared?
	int radius;
	unsigned int color;

	particle(Vector2f position, Vector2f velocity, int radius, unsigned int color);

	void applyforces(int dt);
	void render();

};
#endif
