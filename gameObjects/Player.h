#ifndef PLAYER_H_
#define PLAYER_H_


#include "Vector2f.h"
#include "Entity.h"
#include "RigidBody.h"
#include "Polygon.h"
#include "Sprite.h"
#include "Animation.h"



class Player: public Entity, public RigidBody {
protected:

	float getMaxThrottle();
	float startT;
	Vector2f getShotPos();
	Vector2f getShotVel(float velocity);

	void checkHits();
	Sprite sprite;
	Animation exhaust1;
	Animation exhaust2;

	const double shotInterval = .2;
	double lastShot = 0;

	bool enginesOn = false;

	Polygon* collisionBox;

	void updateSteering();
	void updateCannon();


public:

	float height;

	float maxHealth = 1000;
	float maxEnergy = 1000;

	float health = maxHealth;
	float energy = maxEnergy;

	Player(Vector2f pos, Vector2f vel); //float mass, Vector2f startpos, Vector2f startvel);
	virtual ~Player();

	void update();
	void render();
	void shoot();
	void startTime();

};

extern Player player;

#endif
