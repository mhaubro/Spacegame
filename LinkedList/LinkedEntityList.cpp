/*
 * LinkedEntityList.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: mathi
 */

#include "LinkedEntityList.h"

LinkedEntityList::LinkedEntityList() :
		LinkedList<Entity>() {

}

LinkedEntityList::~LinkedEntityList() {
	while (mHead) {
		Node* next = mHead->mNext;
		delete mHead;
		mHead = next;
	}
}

void LinkedEntityList::updateAll() {
	Node* tmp = mHead;
	while (tmp) {
		tmp->mData->update();
		if (tmp->mData->isDead()){
			tmp->mShouldRemove = true;
		}
		tmp = tmp->mNext;
	}
}

void LinkedEntityList::renderAll() {
	Node* tmp = mHead;
	while (tmp) {
		tmp->mData->render();
		tmp = tmp->mNext;
	}
}

