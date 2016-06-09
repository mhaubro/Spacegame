/*
 * EffectManager.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#include "EffectManager.h"
#include "GD2.h"

#include <algorithm>

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

void EffectManager::update() {
	for (std::vector<Effect *>::iterator it = mEffects.begin();
			it != mEffects.end(); ++it) {
		((Effect*) *it)->update();
	}
	mEffects.erase(std::remove_if(mEffects.begin(), mEffects.end(), isDead),
			mEffects.end());
}

void EffectManager::render() {

	GD.RestoreContext();
	GD.Begin(BITMAPS);
	for (std::vector<Effect *>::iterator it = mEffects.begin();
			it != mEffects.end(); ++it) {
		((Effect*) *it)->render();
	}
}

void EffectManager::addEffect(Effect * _effect) {
	mEffects.push_back(_effect);
}

