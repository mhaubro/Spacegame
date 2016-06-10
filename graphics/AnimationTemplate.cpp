/*
 * Animation.cpp
 *
 *  Created on: May 13, 2016
 *      Author: mathi
 */

#include "AnimationTemplate.h"
#include "GameTimer.h"
#include "GD2.h"
#include "arduino.h"
#include "Graphics.h"

#define SQRT2 1.41

AnimationTemplate::AnimationTemplate(unsigned char BitMapHandle,
		unsigned short imageWidth, unsigned short imageHeight,
		unsigned char startCell, unsigned char frames, double Interval) :
		id(BitMapHandle), width(imageWidth), height(imageHeight), startCell(
				startCell), frames(frames), frameInterval(Interval), offsetX(
				(imageWidth * SQRT2) / (UNIT * 2)), offsetY(
				(imageHeight * SQRT2) / (UNIT * 2)) {
}

AnimationTemplate::~AnimationTemplate() {
}

void AnimationTemplate::renderFrame(const float x, const float y,
		const float angle, const float scale, unsigned short frame) {
	GD.BitmapHandle(id);
	GD.Cell(startCell + frame);
	GD.BitmapSize(BILINEAR, BORDER, BORDER, scale * width * SQRT2,
			scale * height * SQRT2);
	GD.cmd_loadidentity();
	GD.cmd_translate(F16(scale * width * SQRT2 / 2),
			F16(scale * height * SQRT2 / 2));
	GD.cmd_rotate(FURMANS(angle));
	GD.cmd_translate(F16(-scale * width / 2), F16(-scale * height / 2));
	GD.cmd_scale(F16(scale), F16(scale));
	GD.cmd_setmatrix();
	cam.Vertex2f(x - offsetX * scale, y + offsetY * scale);
}

void AnimationTemplate::render(const float x, const float y, const float angle,
		const float scale, unsigned char * frame, double * lastFrame) {

	if (frame && lastFrame) {
		if (timer.getRunTime() > *lastFrame + frameInterval) {
			*frame = ++*frame % frames;
			*lastFrame = timer.getRunTime();
		}

		renderFrame(x, y, angle, scale, *frame);
	}
}

void AnimationTemplate::render(const Vector2f pos, const float angle,
		const float scale, unsigned char * frame, double * lastFrame) {

	if (frame && lastFrame) {
		if (timer.getRunTime() > *lastFrame + frameInterval) {
			*frame = ++*frame % frames;
			*lastFrame = timer.getRunTime();
		}

		renderFrame(pos.x, pos.y, angle, scale, *frame);
	}
}
