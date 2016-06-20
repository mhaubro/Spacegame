/*
 * Behavior.h
 *
 *  Created on: 20/06/2016
 *      Author: Martin
 */

#ifndef SRC_ENEMY_BEHAVIORS_BEHAVIOR_H_
#define SRC_ENEMY_BEHAVIORS_BEHAVIOR_H_

class Enemy;
class Behavior {
protected:
	Enemy * enemy;


public:
	Behavior(Enemy * _enemy);
	virtual ~Behavior();

	virtual void update();

};

#endif /* SRC_ENEMY_BEHAVIORS_BEHAVIOR_H_ */
