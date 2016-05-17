/*
 * Animation.cpp
 *
 *  Created on: May 13, 2016
 *      Author: mathi
 */

#include "Animation.h"
#include "GameTimer.h"

Animation::Animation(Sprite* sprite, double interval, unsigned char maxFrame) :
		sprite(sprite), lastFrame(0), frameInterval(interval), maxFrame(
				maxFrame), frame(0) {
}

Animation::~Animation() {
}

void Animation::render(const float x, const float y, const float angle,
		const float scale) {
	if (sprite != NULL) {

		if (timer.getRunTime() > lastFrame + frameInterval) {
			frame = ++frame % maxFrame;
			lastFrame = timer.getRunTime();
		}

		sprite->render(x, y, angle, scale, frame);
	}
}

void Animation::render(const Vector2f pos, const float angle,
		const float scale) {
	if (sprite != NULL) {

		if (timer.getRunTime() > lastFrame + frameInterval) {
			frame = ++frame % maxFrame;
			lastFrame = timer.getRunTime();
		}

		sprite->render(pos.x, pos.y, angle, scale, frame);
	}
}
