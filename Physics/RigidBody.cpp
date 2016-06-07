#include "RigidBody.h"

RigidBody::RigidBody(float mass, float inertia, Vector2f position, float angle,
		Vector2f velocity) :
		PhysicsObject(mass, position, velocity), inertia(inertia), angle(angle) {
}

RigidBody::~RigidBody(){

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

float RigidBody::getInertia(){
	return inertia;
}

float RigidBody::getAngle(){
	return angle;
}

float RigidBody::getAngularVelocity(){
	return aVelocity;
}

float RigidBody::getAngularAcceleration(){
	return aAcceleration;
}
float RigidBody::getTorque(){
	return aTorque;
}

