/*
 * GameTimer.cpp
 *
 *  Created on: May 13, 2016
 *      Author: mathi
 */

#include "GameTimer.h"

GameTimer timer;

GameTimer::GameTimer() {
	t.start(); //HUSK AT STARTE TIMER

}

GameTimer::~GameTimer() {
	// TODO Auto-generated destructor stub
}

void GameTimer::update() {
	deltatime = t.read();
	runtime += deltatime;
	t.reset();

}

float GameTimer::getDeltaTime() {
	return deltatime;
}

double GameTimer::getRunTime() {
	return runtime;
}

