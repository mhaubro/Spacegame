#pragma once

#include "mbed.h"
#include "GD2.h"
#include "Vector2f.h"

#define UNIT (float) 16
#define UNIT16 (float) 16 * UNIT

#define PI2 ((float)PI*2)
#define FURMANS(n) (uint16_t)((65536UL * (n/PI2)))

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define SCREEN_MIN_X -40
#define SCREEN_MIN_Y -20
#define SCREEN_MAX_X 40
#define SCREEN_MAX_Y 20

#define SCREEN_UNIT_BORDER_X (float) SCREEN_WIDTH / (2 * UNIT)
#define SCREEN_UNIT_BORDER_Y (float) SCREEN_HEIGHT / (2 * UNIT)

#define BLACK 0x000000
#define WHITE 0xffffff
#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff
#define GREY 0x888888
#define DARK_GREY 0x444444
#define BROWN 0xB07A45
#define COLOR_ENERGY 0xffff22
#define COLOR_HEALTH 0xff0000
#define COLOR_SHIELD 0x22aaff

#define CAM_X_OFFSET16 SCREEN_WIDTH * 8
#define CAM_Y_OFFSET16 SCREEN_HEIGHT * 8

class Cam
{
protected:
	Vector2f pos;

public:
	Cam();
	void translate(Vector2f arg);
	void moveTo(Vector2f arg);
	short getX();
	short getY();
	void Vertex2f(float x, float y);

};

extern Cam cam;

void resetGraphics();
