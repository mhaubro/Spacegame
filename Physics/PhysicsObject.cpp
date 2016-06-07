#include "PhysicsObject.h"
#include "PhysicsConstants.h"
#include "GD2.h"
#include "graphics.h"
#include "GameTimer.h"

PhysicsObject::PhysicsObject(float mass, Vector2f& position, Vector2f& velocity) :
		mass(mass), position(position), velocity(velocity) {
}

void PhysicsObject::updatePhysics() {
	float dt = timer.getDeltaTime();
	accelerations += forces * (1 / mass);
	velocity += accelerations * dt;
	position += velocity * dt;
	accelerations = 0;
	forces = 0;

	if (position.y > 100) {
		position.y = 100;
		velocity.y *= -.1;
	}

	if (position.y < 0) {
		position.y = 0;
		velocity.y *= -.1;
	}

	while (position.x > WORLD_SIZE * CHUNK_SIZE) {
		position.x -= WORLD_SIZE * CHUNK_SIZE;
	}
	while (position.x < 0) {
		position.x += WORLD_SIZE * CHUNK_SIZE;
	}

}

void PhysicsObject::addForce(Vector2f v) {
	forces += v;
}

void PhysicsObject::addAcceleration(Vector2f v) {
	accelerations += v;
}

Vector2f PhysicsObject::getPosition(){
	return position;
}

Vector2f PhysicsObject::getVelocity(){
	return velocity;
}

float PhysicsObject::getMass(){
	return mass;
}
