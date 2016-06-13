#ifndef PLAYER_H_
#define PLAYER_H_


#include "Vector2f.h"
#include "Entity.h"
#include "RigidBody.h"
#include "Polygon.h"
#include "Sprite.h"
#include "Animation.h"

#define MAX_PLAYER_HEALTH 1000
#define MAX_PLAYER_ENERGY 1000

class Player: public Entity, public RigidBody {
protected:

	float startT;

	Sprite sprite;
	Animation exhaust1;
	Animation exhaust2;

	const double shotInterval;
	double lastShot;

	bool enginesOn;

	Polygon* collisionBox;

	void checkHits();

	float getMaxThrottle();
	void updateSteering();
	void updateCannon();

	Vector2f getShotPos();
	Vector2f getShotVel(float velocity);

public:

	float height;

	float health;
	float energy;

	Player(Vector2f pos, Vector2f vel); //float mass, Vector2f startpos, Vector2f startvel);
	virtual ~Player();

	void update();
	void render();
	void shoot();
	void startTime();

};

extern Player player;

#endif
