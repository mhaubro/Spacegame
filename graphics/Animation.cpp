/*
 * Animation.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#include "Animation.h"

Animation::Animation(AnimationTemplate & _template, Vector2f _position,
		float _angle, float _scale) :
		mTemplate(_template), mPosition(_position), mAngle(_angle), mScale(
				_scale){
	// TODO Auto-generated constructor stub

}

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

void Animation::render() {
	mTemplate.render(mPosition, mAngle, mScale, &mFrame, &mLastFrame);
}

Vector2f Animation::getPosition() {
	return mPosition;
}

float Animation::getAngle() {
	return mAngle;
}

float Animation::getScale() {
	return mScale;
}

void Animation::setPosition(Vector2f _position) {
	mPosition = _position;
}

void Animation::setAngle(float _angle) {
	mAngle = _angle;
}

void Animation::setScale(float _scale) {
	mScale = _scale;
}

