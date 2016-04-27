#pragma once

#include "GD2.h"
#include "mbed.h"
#include "Graphics.h"
#include <time.h>
#include <string.h>
#include "Input.h"
#include "PhysicsConstants.h"
#include "myassets.h"
#include "vector2f.h"
#include "PhysicsObject.h"
#include "button.h"

class Physicstest{

public:
	void run();
	void runloop(Input in, Timer t, float *lasttime, float *currtime, char str[], PhysicsObject* ph1, PhysicsObject* ph2, Button button);
	Physicstest();
	void drawText(char str[], Timer t);

	void checkCollision(Vector2f& position, Vector2f& velocity, int pointsize);

protected:
	void initPoints();

};

