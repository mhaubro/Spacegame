/*
 * Entity.cpp
 *
 *  Created on: May 17, 2016
 *      Author: mathi
 */

#include "Entity.h"

Entity::Entity(Vector2f& pos, Vector2f& vel, float mass) : ph(new PhysicsObject(mass, pos, vel))
{
}

Entity::~Entity() {
	delete ph;
}

