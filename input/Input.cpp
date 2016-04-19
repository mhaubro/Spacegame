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

bool Input::getThrodle() {
	// TODO implement button
	return false;
}

float Input::getRotation() {
	return (float)ax * 10;
}
