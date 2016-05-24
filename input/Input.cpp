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
	getAcceleration(ax,ay);
}

bool Input::getThrottle() {
	if (GD.inputs.x != -32768){
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
	return (float)ax;
}
