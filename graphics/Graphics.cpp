#include "Graphics.h"



Cam cam;

Cam::Cam()
: pos(), offset()
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

void Cam::follow(Vector2f position, Vector2f velocity){
	float off = 0;
	Vector2f downpull = Vector2f();//Styrer hvor meget, der "trækkes ned", så jorden ikke fylder 50 %
	if (position.y < CAM_GROUND_OFFSET){
		off = (position.y/CAM_GROUND_OFFSET);

		off = (1-off)*CAM_GROUND_OFFSET;

	}
	offset.x = (15*offset.x + velocity.x * 1)/16;
	offset.y = (15*offset.y + velocity.y * 0.5)/16;
	pos = position + offset;
	pos.y += off;
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
void Cam::Vertex2f(Vector2f arg)
{
	Vertex2f(arg.x, arg.y);
}

void renderVector2f(Vector2f &arg, float x, float y, float scale){

	GD.PointSize(16 * 2);
	GD.Begin(POINTS);
	cam.Vertex2f(x,y);

	GD.LineWidth(16 * 1);
	GD.Begin(LINES);
	cam.Vertex2f(x,y);
	cam.Vertex2f(x+arg.x*scale,y+arg.y*scale);

}

void resetGraphics()
{
	// TODO reset all graphics settings to something normal
}

