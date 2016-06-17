//Author: MG

#ifndef SRC_GRAPHICS_ANIMATIONTEMPLATE_H_
#define SRC_GRAPHICS_ANIMATIONTEMPLATE_H_

class AnimationTemplate;

#include "Vector2f.h"

class AnimationTemplate {
protected:

	const unsigned char id;
	const unsigned short width, height;

	unsigned char startCell;
	unsigned char frames;

	double frameInterval;

	const float offsetX, offsetY;

	void renderFrame(const float x, const float y, const float angle,
			const float scale, unsigned short frame);

public:

	AnimationTemplate(unsigned char BitMapHandle, unsigned short imageWidth,
			unsigned short imageHeight, unsigned char startCell,
			unsigned char frames, double Interval);
	virtual ~AnimationTemplate();

	void render(const float x, const float y, const float angle,
			const float scale, unsigned char * frame, double * lastFrame);
	void render(const Vector2f pos, const float angle, const float scale,
			unsigned char * frame, double * lastFrame);
};

#endif /* SRC_GRAPHICS_ANIMATIONTEMPLATE_H_ */
