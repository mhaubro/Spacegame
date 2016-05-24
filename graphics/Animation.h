/*
 * Animation.h
 *
 *  Created on: May 13, 2016
 *      Author: mathi
 */

#ifndef SRC_GRAPHICS_ANIMATION_H_
#define SRC_GRAPHICS_ANIMATION_H_

class Animation;

#include "Vector2f.h"

class Animation {
protected:
	void renderFrame(const float x, const float y, const float angle,
			const float scale, unsigned short frame);

public:

	const unsigned char id;
	const unsigned short width, height;

	unsigned char startCell;
	unsigned char frames;

	double lastFrame;
	double frameInterval;

	unsigned char frame;

	const float offsetX, offsetY;

	Animation(unsigned char BitMapHandle, unsigned short imageWidth,
			unsigned short imageHeight, unsigned char startCell, unsigned char frames, double Interval);
	virtual ~Animation();

	void render(const float x, const float y, const float angle,
			const float scale);
	void render(const Vector2f pos, const float angle, const float scale);
};

#endif /* SRC_GRAPHICS_ANIMATION_H_ */
