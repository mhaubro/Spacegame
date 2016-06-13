/*
 * LinkedEntityList.h
 *
 *  Created on: Jun 12, 2016
 *      Author: mathi
 */

#ifndef SRC_LINKEDLIST_LINKEDENTITYLIST_H_
#define SRC_LINKEDLIST_LINKEDENTITYLIST_H_

#include "Entity.h"
#include "LinkedList.h"

class LinkedEntityList : public LinkedList<Entity> {

public:
	LinkedEntityList();
	virtual ~LinkedEntityList();

	virtual void updateAll();
	virtual void renderAll();

};

#endif /* SRC_LINKEDLIST_LINKEDENTITYLIST_H_ */
