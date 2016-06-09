/*
 * Entity.h
 *
 *  Created on: May 17, 2016
 *      Author: mathi
 */

#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

#include "PhysicsObject.h"

class Entity{
protected:

	Entity();

public:
	virtual ~Entity();

	virtual void update();
	virtual void render();

	virtual bool collide(Entity entity);

	bool isDead = false;
};

#endif /* SRC_ENTITY_H_ */
