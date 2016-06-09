/*
 * StaticAnimationEffect.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#include "StaticAnimationEffect.h"
#include "GameTimer.h"

StaticAnimationEffect::StaticAnimationEffect(Vector2f _position, double _lifespan,
		AnimationTemplate& _template) :
		Effect(_position), mAnimation(_template, _position, 0.0f, 1.0f), mStartTime(
				timer.getRunTime()), mLifespan(_lifespan), mIsDead(false) {

}

StaticAnimationEffect::~StaticAnimationEffect() {
	// TODO Auto-generated destructor stub
}

void StaticAnimationEffect::update() {
	if (timer.getRunTime() > mStartTime + mLifespan) {
		mIsDead = true;
	}
}

void StaticAnimationEffect::render() {
	if (!mIsDead) {
		mAnimation.render();
	}
}

bool StaticAnimationEffect::isDead(){
	return mIsDead;
}

