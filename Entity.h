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

	bool mIsDead;
	Entity();
	bool isEDead;//is Entity Dead.

public:
	virtual ~Entity();

	virtual void update();
	virtual void render();

	virtual void kill();
	virtual bool isDead();


};

#endif /* SRC_ENTITY_H_ */
