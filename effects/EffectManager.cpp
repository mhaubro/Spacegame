/*
 * EffectManager.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#include "EffectManager.h"
#include "GD2.h"
#include "Game.h"

EffectManager::EffectManager(): mEffects() {
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

EffectManager::EffectList::EffectList(): LinkedList<Effect>(){
}

EffectManager::EffectList::~EffectList(){
}

bool EffectManager::EffectList::shouldRemove(Node* node){
	return node->mData->isDead();
}

void EffectManager::EffectList::updateAll() {
	Node* tmp = mHead;
	while (tmp) {
		tmp->mData->update();
		tmp = tmp->mNext;
	}
}

void EffectManager::EffectList::renderAll(){
	Node* tmp = mHead;
	while (tmp){
		tmp->mData->render();
		tmp = tmp->mNext;
	}
}

