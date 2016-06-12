/*
 * LinkedEntityList.h
 *
 *  Created on: Jun 12, 2016
 *      Author: mathi
 */

#ifndef SRC_LINKEDLIST_LINKEDENTITYLIST_H_
#define SRC_LINKEDLIST_LINKEDENTITYLIST_H_

#include "Entity.h"

class LinkedEntityList {
private:
	struct Node {
		Entity * mData;
		Node * mNext;
		Node(Entity* _data, Node* _next) :
				mData(_data), mNext(_next) {
		}
		~Node(){
			delete mData;
		}
	};

	Node* mHead;
	int mSize;

public:
	LinkedEntityList();
	virtual ~LinkedEntityList();

	void updateAll();
	void renderAll();
	void removeDead();
	void add(Entity* e);

	int size();
};

#endif /* SRC_LINKEDLIST_LINKEDENTITYLIST_H_ */
