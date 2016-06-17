//Author: MG

#include "RigidBody.h"
#include "GameTimer.h"
#include "arduino.h"

RigidBody::RigidBody(float mass, float inertia, Vector2f position, float angle,
		Vector2f velocity) :
		PhysicsObject(mass, position, velocity), inertia(inertia), angle(angle), aVelocity(
				0), aAcceleration(0), aTorque(0) {
}

RigidBody::~RigidBody() {

}

void RigidBody::updatePhysics() {
	float dt = timer.getDeltaTime();

	aAcceleration += aTorque / inertia;
	aVelocity += aAcceleration * dt;
	angle += aVelocity * dt;

	while (angle > PI * 2)
		angle -= PI * 2;
	while (angle < 0)
		angle += PI * 2;

	accelerations += forces * (1 / mass);
	velocity += accelerations * dt;
	position += velocity * dt;

	// reseting accumulative variables
	aAcceleration = 0;
	aTorque = 0;
	accelerations = 0;
	forces = 0;

	loopPosition();
}

void RigidBody::addAcceleration(Vector2f v) {
	accelerations += v;
}

void RigidBody::addAngularAcceleration(float _acceleration) {
	aAcceleration += _acceleration;
}

void RigidBody::addTorque(float _torque) {
	aTorque += _torque;
}

void RigidBody::addForce(Vector2f _force, Vector2f point) {

	Vector2f dir = (point - position);

	forces += _force;
	aTorque += dir.length() * _force.scalarProjectAt(dir.rightNormal());

}

void RigidBody::addImpulse(Vector2f impulse, Vector2f point) {

	Vector2f dir = (point - position);

	velocity += impulse / mass;
	aVelocity -= dir.crossproduct(impulse) / inertia;
}

float RigidBody::getInertia() {
	return inertia;
}

float RigidBody::getAngle() {
	return angle;
}

float RigidBody::getAngularVelocity() {
	return aVelocity;
}

float RigidBody::getAngularAcceleration() {
	return aAcceleration;
}
float RigidBody::getTorque() {
	return aTorque;
}

