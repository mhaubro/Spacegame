/*
 * Animation.cpp
 *
 *  Created on: May 13, 2016
 *      Author: mathi
 */

#include "Animation.h"
#include "GameTimer.h"

Animation::Animation(Sprite* sprite, double interval, unsigned char maxFrame) :
		sprite(sprite) , frameInterval(interval), maxFrame(maxFrame){
}

Animation::~Animation() {
}

void Animation::render(const float x, const float y, const float angle, const float scale){
	if (sprite != NULL){

		if (timer.getRunTime() > lastFrame + frameInterval){
			frame = ++frame % maxFrame;
			lastFrame = timer.getRunTime();
		}

		sprite->render(x,y,angle,scale, frame);
	}
}

