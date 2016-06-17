//Author: MH

#include "Sprite.h"

Sprite::Sprite(SpriteTemplate & _template, Vector2f _position, float _angle,
		float _scale) :
		mTemplate(_template), mPosition(_position), mAngle(_angle), mScale(_scale) {
}

Sprite::~Sprite() {
}

void Sprite::render() {
	mTemplate.render(mPosition, mAngle, mScale);
}

Vector2f Sprite::getPosition(){
	return mPosition;
}

float Sprite::getAngle(){
	return mAngle;
}

float Sprite::getScale(){
	return mScale;
}

void Sprite::setPosition(Vector2f _position){
	mPosition = _position;
}

void Sprite::setAngle(float _angle){
	mAngle = _angle;
}

void Sprite::setScale(float _scale){
	mScale = _scale;
}


