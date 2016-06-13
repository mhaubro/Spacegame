/*
 * Entity.cpp
 *
 *  Created on: May 17, 2016
 *      Author: mathi
 */

#include "Entity.h"

Entity::Entity(): mIsDead(false) {
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

void Entity::kill(){
	mIsDead = true;
}

bool Entity::isDead(){
	return mIsDead;
}
