/*
 * GameTimer.h
 *
 *  Created on: May 13, 2016
 *      Author: mathi
 */

#ifndef SRC_GAMETIMER_H_
#define SRC_GAMETIMER_H_

#include "mbed.h"

class GameTimer {

protected:
	double runtime = 0;
	float deltatime = 0;
	Timer t;

public:
	GameTimer();
	virtual ~GameTimer();

	void update();

	float getDeltaTime();
	double getRunTime();
};

extern GameTimer timer;

#endif /* SRC_GAMETIMER_H_ */
