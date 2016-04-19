#include "Graphics.h"

Cam cam;

Cam::Cam()
: _x(0), _y(0)
{
}

void Cam::translate(float dx, float dy)
{
	_x+=dx;
	_y+=dy;
}

void Cam::moveTo(float x, float y)
{
	_x = x;
	_y = y;
}

short Cam::getX()
{
	return _x;
}

short Cam::getY()
{
	return _y;
}

void Cam::Vertex2f(float x, float y)
{
	GD.Vertex2f(UNIT16 * (x - _x) + CAM_X_OFFSET16, UNIT16 * (-y + _y) + CAM_Y_OFFSET16);
}

