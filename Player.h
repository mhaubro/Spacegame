#pragma once

#include "Vector2f.h"
#include "PhysicsObject.h"

class Player {
protected:

public:

	//PhysicsObject ph;
	float angle;

	float height;

	Player();//float mass, Vector2f startpos, Vector2f startvel);

	void update(float t);
	void render();

};
