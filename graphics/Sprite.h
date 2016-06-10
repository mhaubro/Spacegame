/*
 * Sprite.h
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#ifndef SRC_GRAPHICS_SPRITE_H_
#define SRC_GRAPHICS_SPRITE_H_

#include "SpriteTemplate.h"

class Sprite {
protected:
	SpriteTemplate & mTemplate;
	Vector2f mPosition;
	float mAngle;
	float mScale;

public:
	Sprite(SpriteTemplate & _template, Vector2f _position, float _angle,
			float _scale);
	virtual ~Sprite();

	virtual void render();

	void setPosition(Vector2f _position);
	void setAngle(float _angle);
	void setScale(float _scale);
	Vector2f getPosition();
	float getAngle();
	float getScale();

};

#endif /* SRC_GRAPHICS_SPRITE_H_ */
