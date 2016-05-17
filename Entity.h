/*
 * Entity.h
 *
 *  Created on: May 17, 2016
 *      Author: mathi
 */

#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

#include "PhysicsObject.h"

class Entity {
protected:
	PhysicsObject * const ph;

	Entity(Vector2f& pos, Vector2f& vel, float mass);

public:
	virtual ~Entity();

	virtual void update();
	virtual void render();
};

#endif /* SRC_ENTITY_H_ */
