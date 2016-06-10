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
}

Input::~Input() {
}

void Input::pull() {
	GD.get_inputs();
	getAcceleration(ax, ay, az);

}

float Input::calculateAngle() {

	float dot = ay * ay + az * az;
	if (dot == 0){
		return (float) PI / 2;
	}

	float length = sqrtf(ay * ay + az * az)
			* sqrtf(ax * ax + ay * ay + az * az);

	if (length == 0) return 0;

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
	return ((float) ax)*0.0065;
}
