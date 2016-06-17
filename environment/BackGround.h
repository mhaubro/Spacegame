//Author: MH

#ifndef BACKGROUND_H
#define BACKGROUND_H

#define BACKGROUND_WIDTH 256
#define BACKGROUND_HEIGHT 256

#include "GD2.h"
#include "PhysicsObject.h"

class BackGround{

private:

	Vector2f position;
	Vector2f minPos;
	Vector2f maxPos;

	float getBlendFactor();

public:
	void render();
	void update();
	BackGround();
};

extern BackGround Background;

#endif
