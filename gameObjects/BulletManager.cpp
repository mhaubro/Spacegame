//Author: MH

#include <algorithm>
#include "BulletManager.h"
#include "Game.h"

BulletManager::BulletManager() {
}

BulletManager::~BulletManager() {
}

void BulletManager::update() {
	mBullets.updateAll();
	mBullets.clean();
}

void BulletManager::render() {

	GD.RestoreContext();
	GD.Begin(BITMAPS);

	mBullets.renderAll();

#if DEBUG
	GD.RestoreContext();
	GD.cmd_text(4, 120, 16, OPT_SIGNED, "Bullets:");
	GD.cmd_number(70, 120, 16, OPT_SIGNED, mBullets.size());
#endif
}

void BulletManager::addBullet(Bullet * _bullet) {
	mBullets.add(_bullet);
}

BulletManager::BulletList::BulletList(): LinkedList<Bullet>(){
}

BulletManager::BulletList::~BulletList(){
}

bool BulletManager::BulletList::shouldRemove(Node* node){
	return node->mData->isDead();
}

void BulletManager::BulletList::updateAll(){
	Node* tmp = mHead;
	while (tmp){
		tmp->mData->update();
		tmp = tmp->mNext;
	}
}

void BulletManager::BulletList::renderAll(){
	Node* tmp = mHead;
	while (tmp){
		tmp->mData->render();
		tmp = tmp->mNext;
	}
}
