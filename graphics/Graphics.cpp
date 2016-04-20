#include "Graphics.h"

Cam cam;

Cam::Cam()
: pos()
{
}

void Cam::translate(Vector2f arg)
{
	pos += arg;
}

void Cam::moveTo(Vector2f arg)
{
	pos = arg;
}

short Cam::getX()
{
	return pos.x;
}

short Cam::getY()
{
	return pos.y;
}

void Cam::Vertex2f(float x, float y)
{
	float X = (x - pos.x);
	float Y = (-y + pos.y);
	if (X < SCREEN_MIN_X || X > SCREEN_MAX_X || Y < SCREEN_MIN_Y || Y > SCREEN_MAX_Y){
		return;
	}
	GD.Vertex2f(UNIT16 * X + CAM_X_OFFSET16, UNIT16 * Y + CAM_Y_OFFSET16);
}

void resetGraphics()
{
	// TODO reset all graphics settings to something normal
}

