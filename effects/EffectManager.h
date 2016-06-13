/*
 * EffectManager.h
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#ifndef SRC_EFFECTS_EFFECTMANAGER_H_
#define SRC_EFFECTS_EFFECTMANAGER_H_

#include "Effect.h"
#include "LinkedEntityList.h"

class EffectManager {
protected:

	LinkedEntityList mEffects;

public:
	EffectManager();
	virtual ~EffectManager();

	virtual void update();
	virtual void render();

	void addEffect(Effect * effect);
};

#endif /* SRC_EFFECTS_EFFECTMANAGER_H_ */
