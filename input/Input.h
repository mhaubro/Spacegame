/*
 * Input.h
 *
 *  Created on: Apr 19, 2016
 *      Author: mathias
 */

#ifndef SRC_INPUT_INPUT_H_
#define SRC_INPUT_INPUT_H_

#include "Accelerometer.h"
#include "Button.h"

class Input {
protected:
	//Button b1 = new Button();
	int ax = 0, ay = 0, az = 0;
	float angle;

public:
	Input();
	virtual ~Input();

	void pull();

	bool getThrottle();
	float getRotation();

	bool getLeftTouch();
	bool getRightTouch();

	float calculateAngle();

};

extern Input input;

#endif /* SRC_INPUT_INPUT_H_ */
