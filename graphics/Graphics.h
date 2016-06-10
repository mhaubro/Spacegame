#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "mbed.h"
#include "GD2.h"
#include "Vector2f.h"
#include "World.h"
#include "Game.h"

#define UNIT (float) 16
#define UNIT16 (float) 16 * UNIT

#define PI2 ((float)PI*2)
#define FURMANS(n) (uint16_t)((65536UL * (n/PI2)))

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define SCREEN_MIN_X -20
#define SCREEN_MIN_Y -20
#define SCREEN_MAX_X 20
#define SCREEN_MAX_Y 20

#define SCREEN_UNIT_BORDER_X (float) SCREEN_WIDTH / (2 * UNIT)
#define SCREEN_UNIT_BORDER_Y (float) SCREEN_HEIGHT / (2 * UNIT)

#define BLACK 0x000000
#define WHITE 0xffffff
#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff
#define YELLOW 0xffff00
#define PURPLE 0xff00ff
#define ORANGE 0xff7700
#define GREY 0x888888
#define DARK_GREY 0x444444
#define BROWN 0xB07A45
#define SKY 0x803900
#define COLOR_ENERGY 0xffff22
#define COLOR_HEALTH 0xff0000
#define COLOR_SHIELD 0x22aaff

#define CAM_X_OFFSET16 SCREEN_WIDTH * 8
#define CAM_Y_OFFSET16 SCREEN_HEIGHT * 8

#define OFFSET_FACTOR 11

#define CAM_GROUND_OFFSET 8

class Cam
{
protected:
	Vector2f pos;
	Vector2f offset;

public:
	Cam();
	void translate(Vector2f arg);
	void moveTo(Vector2f arg);
	void follow(Vector2f pos, Vector2f vel);
	short getX();
	short getY();
	void Vertex2f(float x, float y);
	void Vertex2f(Vector2f arg);
};
extern Cam cam;


unsigned int blend(unsigned int color1, unsigned int color2, float blendfactor);
void renderVector2f(Vector2f &arg, float x, float y, float scale);

void resetGraphics();

void initGraphics();

#endif
