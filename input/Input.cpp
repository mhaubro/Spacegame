/*
 * Input.cpp
 *
 *  Created on: Apr 19, 2016
 *      Author: mathias
 */

#include "Input.h"

Input input;

Input::Input() {
	resetAcceleration();
	button1 = new Button(PB_13);
	button2 = new Button(PB_14);
	button3 = new Button(PB_15);
	button4 = new Button(PB_1);
}

Input::~Input() {
	delete button1;
	delete button2;
	delete button3;
	delete button4;
}

void Input::pull() {
	GD.get_inputs();
	getAcceleration(ax, ay, az);

}

float Input::calculateAngle() {

	float dot = ay * ay + az * az;
	if (dot == 0) {
		return (float) PI / 2;
	}

	float length = sqrtf(ay * ay + az * az)
			* sqrtf(ax * ax + ay * ay + az * az);

	if (length == 0)
		return 0;

	if (dot < 0) {
		return acosf(dot / length) + PI;
	} else {
		return acosf(dot / length);
	}

}

bool Input::getThrottle() {
	if (GD.inputs.x != -32768) {
		return true;
	}
	return false;
}

bool Input::getLeftTouch() {
	return (GD.inputs.x > 0 && GD.inputs.x < 240);
}

bool Input::getRightTouch() {
	return (GD.inputs.x > 240 && GD.inputs.x < 480);
}

float Input::getRotation() {
	return ((float) ax) * 0.0065;
}

#if USE_BUTTONS
bool Input::getButton1() {
	return button1->isPressed();
}
#else
bool Input::getButton1(){
	return getLeftTouch();
}
#endif

bool Input::getButton2() {
	return button2->isPressed();
}

#if USE_BUTTONS
bool Input::getButton3(){
	return button3->isPressed();
}
#else
bool Input::getButton3(){
	return getRightTouch();
}
#endif

bool Input::getButton4(){
	return button4->isPressed();
}
