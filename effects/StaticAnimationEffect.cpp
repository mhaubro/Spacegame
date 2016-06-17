//Author: MG

#include "StaticAnimationEffect.h"
#include "GameTimer.h"

StaticAnimationEffect::StaticAnimationEffect(Vector2f _position, double _lifespan,
		AnimationTemplate& _template, float _angle, float _scale) :
		Effect(_position), mAnimation(_template, _position, _angle, _scale), mStartTime(
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

