
#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "PhysicsObject.h"

class RigidBody: public PhysicsObject {

protected:

	float inertia;

	float angle; //Angle of unit, radians.
	float aVelocity;
	float aAcceleration;
	float aTorque;

public:

	RigidBody(float mass, float inertia, Vector2f position, float angle, Vector2f velocity);
	virtual ~RigidBody();

	virtual void addAcceleration(Vector2f v);
	virtual void addAngularAcceleration(float acceleration);
	virtual void addForce(Vector2f v, Vector2f point);
	virtual void addTorque(float torque);
	virtual void updatePhysics();

	float getInertia();
	float getAngle();
	float getAngularVelocity();
	float getAngularAcceleration();
	float getTorque();

};

#endif
