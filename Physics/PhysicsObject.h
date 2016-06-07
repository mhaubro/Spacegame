

#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "PhysicsConstants.h"
#include "Vector2f.h"
#include "World.h"

class PhysicsObject {

public:
	float mass;
	float radius;
	Vector2f forces;
	Vector2f accelerations;
	Vector2f position;
	Vector2f velocity;

	PhysicsObject(float mass, Vector2f& position, Vector2f& velocity);

//	Vector2f& getPosition();
//	Vector2f& getVelocity();//Maybe implement?
	void render();

	void addAcceleration(Vector2f v);
	void addForce(Vector2f v);
	void update();

};
#endif
