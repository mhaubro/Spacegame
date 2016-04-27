/*
 * Input.cpp
 *
 *  Created on: Apr 19, 2016
 *      Author: mathias
 */

#include "Input.h"

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

float Input::getRotation() {
	return (float)ax;
}
