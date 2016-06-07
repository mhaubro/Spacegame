#include "RigidBody.h"
#include "GameTimer.h"

RigidBody::RigidBody(float mass, float inertia, Vector2f position, float angle,
		Vector2f velocity) :
		PhysicsObject(mass, position, velocity), inertia(inertia), angle(angle) {
}

RigidBody::~RigidBody() {

}

void RigidBody::updatePhysics() {
	float dt = timer.getDeltaTime();

	aAcceleration += aTorque / inertia;
	aVelocity += aAcceleration * dt;
	angle += aVelocity * dt;


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
	forces += _force;
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

