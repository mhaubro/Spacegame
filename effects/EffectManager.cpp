/*
 * EffectManager.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#include "EffectManager.h"
#include "GD2.h"
#include "Game.h"

EffectManager::EffectManager() {
}

EffectManager::~EffectManager() {
}

void EffectManager::update() {
	mEffects.updateAll();
	mEffects.clean();
}

void EffectManager::render() {

	GD.RestoreContext();
	GD.Begin(BITMAPS);

	mEffects.renderAll();

#if DEBUG
	GD.RestoreContext();
	GD.cmd_text(4, 100, 16, OPT_SIGNED, "Effects:");
	GD.cmd_number(70, 100, 16, OPT_SIGNED, mEffects.size());
#endif
}

void EffectManager::addEffect(Effect * _effect) {
	mEffects.add(_effect);
}

