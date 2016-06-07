
#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "PhysicsConstants.h"
#include "Vector2f.h"
#include "World.h"

class PhysicsObject {
protected:
	float mass;

	Vector2f forces;
	Vector2f accelerations;
	Vector2f position;
	Vector2f velocity;

public:

	PhysicsObject(float mass, Vector2f& position, Vector2f& velocity);

	void render();

	void addAcceleration(Vector2f v);
	void addForce(Vector2f v);
	void updatePhysics();

	Vector2f getPosition();
	Vector2f getVelocity();
	float getMass();

};
#endif
