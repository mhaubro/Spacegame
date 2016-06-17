//Author: MH

#include "GameTimer.h"

GameTimer timer;

GameTimer::GameTimer()
:deltatime(0), runtime(0)
	{
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

