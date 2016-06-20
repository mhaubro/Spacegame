/*
 * KamikazeBehavior.h
 *
 *  Created on: 20/06/2016
 *      Author: Martin
 */

#ifndef SRC_ENEMY_BEHAVIORS_KAMIKAZEBEHAVIOR_H_
#define SRC_ENEMY_BEHAVIORS_KAMIKAZEBEHAVIOR_H_

#include "Behavior.h"

class KamikazeBehavior : public Behavior {



public:
	KamikazeBehavior(Enemy * enemy);
	virtual ~KamikazeBehavior();

	virtual void update();

};

#endif /* SRC_ENEMY_BEHAVIORS_KAMIKAZEBEHAVIOR_H_ */
