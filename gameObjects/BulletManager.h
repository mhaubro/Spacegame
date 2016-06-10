/*
 * BulletManager.h
 *
 *  Created on: Jun 10, 2016
 *      Author: mathi
 */

#ifndef SRC_GAMEOBJECTS_BULLETMANAGER_H_
#define SRC_GAMEOBJECTS_BULLETMANAGER_H_

#include <vector>

#include "Bullet.h"

class BulletManager {
protected:

	std::vector<Bullet*> mBullets;

public:
	BulletManager();
	virtual ~BulletManager();

	virtual void update();
	virtual void render();

	void addBullet(Bullet * _bullet);

};

#endif /* SRC_GAMEOBJECTS_BULLETMANAGER_H_ */
