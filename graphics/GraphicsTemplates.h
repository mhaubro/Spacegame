/*
 * GraphicsTemplates.h
 *
 *  Created on: Jun 10, 2016
 *      Author: mathi
 */

#ifndef SRC_GRAPHICS_GRAPHICSTEMPLATES_H_
#define SRC_GRAPHICS_GRAPHICSTEMPLATES_H_

#include "SpriteTemplate.h"
#include "AnimationTemplate.h"
#include "myassets.h"

static SpriteTemplate SpaceShipSprite32 = SpriteTemplate(SPRITESHEET32_HANDLE, 32,	32, 0);

static SpriteTemplate Enemy1Sprite32 = SpriteTemplate(SPRITESHEET32_HANDLE, 32,	32, 1);
static SpriteTemplate Enemy2Sprite32 = SpriteTemplate(SPRITESHEET32_HANDLE, 32,	32, 2);

static AnimationTemplate GroundCollisionAnimation32 = AnimationTemplate(SPRITESHEET32_HANDLE, 32, 32, 4, 4, .2);
static AnimationTemplate BulletCollisionAnimation32 = AnimationTemplate(SPRITESHEET32_HANDLE, 32, 32, 8, 4, .1);

static AnimationTemplate GroundCollisionAnimation16 = AnimationTemplate(SPRITESHEET16_HANDLE, 16, 16, 0, 6, .2);
static AnimationTemplate BulletCollisionAnimation16 = AnimationTemplate(SPRITESHEET16_HANDLE, 16, 16, 8, 6, .2);

static AnimationTemplate ExhaustAnimation8 = AnimationTemplate(SPRITESHEET8_HANDLE, 8, 8, 9, 2, .1);

static AnimationTemplate BulletTemplate = AnimationTemplate(SPRITESHEET8_HANDLE,
		8, 8, 11, 2, 0.1);

#endif /* SRC_GRAPHICS_GRAPHICSTEMPLATES_H_ */
