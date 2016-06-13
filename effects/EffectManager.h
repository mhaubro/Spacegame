/*
 * EffectManager.h
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#ifndef SRC_EFFECTS_EFFECTMANAGER_H_
#define SRC_EFFECTS_EFFECTMANAGER_H_

#include "Effect.h"
#include "LinkedList.h"

class EffectManager {
protected:

	class EffectList: public LinkedList<Effect> {
	public:
		EffectList();
		virtual ~EffectList();

		virtual void updateAll();
		virtual void renderAll();
		virtual bool shouldRemove(Node* node);
	};

	EffectList mEffects;

public:
	EffectManager();
	virtual ~EffectManager();

	virtual void update();
	virtual void render();

	void addEffect(Effect * effect);
};

#endif /* SRC_EFFECTS_EFFECTMANAGER_H_ */
