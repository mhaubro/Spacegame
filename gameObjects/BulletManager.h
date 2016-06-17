//Author: MH

#ifndef SRC_GAMEOBJECTS_BULLETMANAGER_H_
#define SRC_GAMEOBJECTS_BULLETMANAGER_H_

#include "Bullet.h"
#include "LinkedList.h"

class BulletManager {
protected:

	class BulletList: public LinkedList<Bullet> {
	public:
		BulletList();
		virtual ~BulletList();
		virtual void updateAll();
		virtual void renderAll();
		virtual bool shouldRemove(Node* node);
	};

	BulletList mBullets;

public:
	BulletManager();
	virtual ~BulletManager();

	virtual void update();
	virtual void render();

	void addBullet(Bullet * _bullet);

};

#endif /* SRC_GAMEOBJECTS_BULLETMANAGER_H_ */
