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

#define USE_BUTTONS false

class Input {
protected:

	Button * button1;
	Button * button2;
	Button * button3;
	Button * button4;

	int ax, ay, az;
	float angle;

public:
	Input();
	virtual ~Input();

	void pull();

	bool getThrottle();
	float getRotation();

	bool getLeftTouch();
	bool getRightTouch();

	bool getButton1();
	bool getButton2();
	bool getButton3();
	bool getButton4();

	float calculateAngle();

};

extern Input input;

#endif /* SRC_INPUT_INPUT_H_ */
