
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

	void loopPosition();

public:

	PhysicsObject(float mass, Vector2f& position, Vector2f& velocity);
	PhysicsObject(float mass);
	virtual ~PhysicsObject();

	virtual void addAcceleration(Vector2f v);
	virtual void addForce(Vector2f v, Vector2f point);
	virtual void addImpulse(Vector2f impulse, Vector2f point);
	virtual void updatePhysics();

	Vector2f getPosition();
	Vector2f getVelocity();
	float getMass();

};

#endif
