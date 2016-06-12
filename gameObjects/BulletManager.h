/*
 * BulletManager.h
 *
 *  Created on: Jun 10, 2016
 *      Author: mathi
 */

#ifndef SRC_GAMEOBJECTS_BULLETMANAGER_H_
#define SRC_GAMEOBJECTS_BULLETMANAGER_H_

#include "Bullet.h"
#include "LinkedEntityList.h"

class BulletManager {
protected:

	LinkedEntityList mBullets;

public:
	BulletManager();
	virtual ~BulletManager();

	virtual void update();
	virtual void render();

	void addBullet(Bullet * _bullet);

};

#endif /* SRC_GAMEOBJECTS_BULLETMANAGER_H_ */
