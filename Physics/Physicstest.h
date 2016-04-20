#pragma once

#include "GD2.h"
#include "mbed.h"

#include "myassets.h"
#include "vector2f.h"

class Physicstest{

public:
	void run();
	Physicstest();
	void checkCollision(Vector2f& position, Vector2f& velocity, int pointsize);

protected:
	void initPoints();

};

