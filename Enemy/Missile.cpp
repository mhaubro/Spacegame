/*
 * Missile.cpp
 *
 *  Created on: 20/06/2016
 *      Author: Martin
 */

#include "Missile.h"
#include "Vector2f.h"
#include "Polygon.h"
#include "Behavior.h"
#include "KamikazeBehavior.h"
#include "GraphicsTemplates.h"
#include "Mathematics.h"
#include "Graphics.h"

static Vector2f arr[] = {Vector2f(.5, .5), Vector2f(.5, -.5), Vector2f(-.5, -.5), Vector2f(-.5, .5)};
static std::vector<Vector2f> shape(arr, arr+4);
static Polygon collisionBox = Polygon(4, shape);

Missile::Missile(Vector2f _position, Vector2f _velocity) :
Enemy(100, collisionBox, new KamikazeBehavior(this),
		_position, .5, .25,
		0, _velocity), sprite(Enemy2Sprite32, _position, 0, 1), exhaust(ExhaustAnimation8, _position, angle, 1)
{
	// TODO Auto-generated constructor stub
}

Missile::~Missile() {
	// TODO Auto-generated destructor stub
}


void Missile::render(){

	GD.Begin(BITMAPS);

	float rotateAngle = loop(angle + PI/2, 0 , 2*PI);
	exhaust.setPosition(Vector2f(0,-1).vertexTransformed(position, rotateAngle));
	exhaust.setAngle(rotateAngle);
	exhaust.render();

	sprite.setPosition(position);
	sprite.setAngle(rotateAngle);
	sprite.render();

	renderVector2f(targetAngle, position.x, position.y, 1);

}
