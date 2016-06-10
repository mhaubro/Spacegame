/*
 * EffectManager.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#include "EffectManager.h"
#include "GD2.h"

#include <algorithm>
#include <tr1/memory>

EffectManager::EffectManager() {
}

EffectManager::~EffectManager() {
}

bool isDead(Effect * _effect) {
	if (_effect->isDead()) {
		delete _effect;
		return true;
	}
	return false;
}

void updateEffect(Effect * _effect){
	_effect->update();
}

void renderEffect(Effect * _effect){
	_effect->render();
}

void EffectManager::update() {

	for_each(mEffects.begin(), mEffects.end(),updateEffect);

	mEffects.erase(std::remove_if(mEffects.begin(), mEffects.end(), isDead),
			mEffects.end());
}

void EffectManager::render() {

	GD.RestoreContext();
	GD.Begin(BITMAPS);

	for_each(mEffects.begin(),mEffects.end(),renderEffect);
//	for (auto_ptr it = mEffects.begin();
//			it != mEffects.end(); ++it) {
//		((Effect*) *it)->render();
//	}

	GD.RestoreContext();
	GD.cmd_text(4, 100, 16, OPT_SIGNED, "effects:");
	GD.cmd_number(70, 100, 16, OPT_SIGNED, mEffects.size());
}

void EffectManager::addEffect(Effect * _effect) {
	mEffects.push_back(_effect);
}

