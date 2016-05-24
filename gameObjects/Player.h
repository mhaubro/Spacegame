#ifndef PLAYER_H_
#define PLAYER_H_


#include "Vector2f.h"
#include "Entity.h"
#include "Animation.h"
#include "Polygon.h"

#include "Animation.h"



class Player: public Entity {
protected:

	float getMaxThrottle();

	Sprite* sprite;
	Sprite* exhaust;
	Animation* anim;

	bool isThrust = false;
	bool isDead = false;

	Polygon* collisionBox;

public:

	float angle;

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

};

extern Player player;

#endif
