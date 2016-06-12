/*
 * EffectManager.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#include "EffectManager.h"
#include "GD2.h"

EffectManager::EffectManager() {
}

EffectManager::~EffectManager() {
}

void EffectManager::update() {
	mEffects.updateAll();
	mEffects.removeDead();
}

void EffectManager::render() {

	GD.RestoreContext();
	GD.Begin(BITMAPS);

	mEffects.renderAll();

	GD.RestoreContext();
	GD.cmd_text(4, 100, 16, OPT_SIGNED, "effects:");
	GD.cmd_number(70, 100, 16, OPT_SIGNED, mEffects.size());
}

void EffectManager::addEffect(Effect * _effect) {
	mEffects.add(_effect);
}

