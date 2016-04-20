#pragma once

#include "Vector2f.h"

class Player {
protected:

public:

	float angle;
	Vector2f pos;
	Vector2f vel;

	Player();

	void update(float t);
	void render();

};
