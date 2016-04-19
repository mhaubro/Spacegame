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
	GD.Vertex2f(UNIT16 * (x - pos.x) + CAM_X_OFFSET16, UNIT16 * (-y + pos.y) + CAM_Y_OFFSET16);
}

void resetGraphics()
{
	// TODO reset all graphics settings to something normal
}

