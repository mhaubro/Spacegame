/*
 * Animation.h
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#ifndef SRC_GRAPHICS_ANIMATION_H_
#define SRC_GRAPHICS_ANIMATION_H_

#include "AnimationTemplate.h"
#include "Vector2f.h"

class Animation {
protected:
	AnimationTemplate & mTemplate;
	Vector2f mPosition;
	float mAngle;
	float mScale;
	double mLastFrame;
	unsigned char mFrame;

public:
	Animation(AnimationTemplate & _template, Vector2f _position, float _angle,
			float _scale);
	virtual ~Animation();

	virtual void render();

	void setPosition(Vector2f _position);
	void setAngle(float _angle);
	void setScale(float _scale);

	Vector2f getPosition();
	float getAngle();
	float getScale();
};

#endif /* SRC_GRAPHICS_ANIMATION_H_ */
