/*
 * Effect.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: mathi
 */

#include "Effect.h"

Effect::Effect(Vector2f position) : Entity(), position(position){

}

Effect::~Effect() {
}

void Effect::update(){

}

void Effect::render(){

}

bool Effect::isDead(){
	return false;
}

