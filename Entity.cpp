/*
 * Entity.cpp
 *
 *  Created on: May 17, 2016
 *      Author: mathi
 */

#include "Entity.h"

Entity::Entity(Vector2f& pos, Vector2f& vel, float mass) :
		ph(PhysicsObject(mass, pos, vel)) {
}

Entity::~Entity() {
}

void Entity::update() {

}
void Entity::render() {

}

bool Entity::collide(Entity entity) {
	return false;
}

Vector2f Entity::getPosition() {
	return Vector2f(ph.position);
}

Vector2f Entity::getVelocity() {
	return Vector2f(ph.velocity);
}

