/*
 * Animation.h
 *
 *  Created on: May 13, 2016
 *      Author: mathi
 */

#ifndef SRC_GRAPHICS_ANIMATION_H_
#define SRC_GRAPHICS_ANIMATION_H_

#include "Sprite.h"

class Animation {

public:

	Sprite* sprite;
	double lastFrame = 0;
	double frameInterval;

	unsigned char maxFrame;
	unsigned char frame = 0;

	Animation(Sprite* sprite, double Interval, unsigned char maxFrame);
	virtual ~Animation();

	void render(const float x, const float y, const float angle, const float scale);
};

#endif /* SRC_GRAPHICS_ANIMATION_H_ */
