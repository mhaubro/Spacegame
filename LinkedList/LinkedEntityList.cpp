/*
 * LinkedEntityList.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: mathi
 */

#include "LinkedEntityList.h"

LinkedEntityList::LinkedEntityList() :
		mHead(), size(0) {

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

void LinkedEntityList::removeDead() {
	if (mHead) {
		while (mHead && mHead->mData->isDead){
			Node* next = mHead->mNext;
			delete mHead;
			mHead = next;
		}
		Node* prev = mHead;
		Node* tmp = mHead->mNext;
		while (tmp) {
			if (tmp->mData->isDead) {
				Node* next = tmp->mNext;
				delete tmp;
				tmp = next;
				prev->mNext = tmp;
			}
		}
	}
}

void LinkedEntityList::add(Entity * e) {
	mHead = new Node(e, mHead);
	size++;
}

