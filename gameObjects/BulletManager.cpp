/*
 * BulletManager.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: mathi
 */

#include "BulletManager.h"

BulletManager::BulletManager() {
}

BulletManager::~BulletManager() {
}

void BulletManager::update() {
	mBullets.updateAll();
	mBullets.removeDead();
}

void BulletManager::render() {

	GD.RestoreContext();
	GD.Begin(BITMAPS);

	mBullets.renderAll();

#if DEBUG
	GD.RestoreContext();
	GD.cmd_text(4, 120, 16, OPT_SIGNED, "bullets:");
	GD.cmd_number(70, 120, 16, OPT_SIGNED, mBullets.size());
#endif
}

void BulletManager::addBullet(Bullet * _bullet) {
	mBullets.add(_bullet);
}
