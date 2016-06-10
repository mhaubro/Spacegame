/*
 * BulletManager.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: mathi
 */

#include "BulletManager.h"
#include <algorithm>

BulletManager::BulletManager() {
}

BulletManager::~BulletManager() {
}

bool isBulletDead(Bullet * _bullet) {
	if (_bullet->isDead()) {
		delete _bullet;
		return true;
	}
	return false;
}

void updateBullet(Bullet * _bullet) {
	_bullet->update();
}

void renderBullet(Bullet * _bullet) {
	_bullet->render();
}

void BulletManager::update() {

	for_each(mBullets.begin(), mBullets.end(), updateBullet);

	mBullets.erase(std::remove_if(mBullets.begin(), mBullets.end(), isBulletDead),
			mBullets.end());
}

void BulletManager::render() {

	GD.RestoreContext();
	GD.Begin(BITMAPS);

	for_each(mBullets.begin(), mBullets.end(), renderBullet);

	GD.RestoreContext();
	GD.cmd_text(4, 120, 16, OPT_SIGNED, "bullets:");
	GD.cmd_number(70, 120, 16, OPT_SIGNED, mBullets.size());
}

void BulletManager::addBullet(Bullet * _bullet) {
	mBullets.push_back(_bullet);
}
