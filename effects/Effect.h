/*
 * Effect.h
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#ifndef SRC_EFFECT_H_
#define SRC_EFFECT_H_

#include "Vector2f.h"
#include "Entity.h"

class Effect : public Entity {
protected:
	Effect(Vector2f position);

	Vector2f position;

public:
	virtual ~Effect();

	virtual void update();
	virtual void render();

	virtual bool isDead();
};

#endif /* SRC_EFFECT_H_ */
