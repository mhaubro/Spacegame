#include "BackGround.h"
#include "GD2.h"
#include "utils.h"
#include "myassets.h"
#include "graphics.h"
#include "sprite.h"
#include "Mathematics.h"

void BackGround::render() {

	float f = getBlendFactor();
	GD.RestoreContext();
	GD.ClearColorRGB(blend(BLACK, SKY, f));
	//GD.ClearColorA(255*f);
	//GD.ClearColorRGB(255*f, 255*f, 255*f);
	//GD.ClearColorRGB(SKY);
	GD.SaveContext();
	GD.Clear();

	GD.Begin(BITMAPS);
	GD.BitmapHandle(RANDOMDOTS_HANDLE);
	GD.Cell(RANDOMDOTS_CELLS - 1);
	GD.Cell(RANDOMDOTS_CELLS - 1);
	//GD.BitmapSize(BILINEAR,REPEAT,REPEAT,(2*64+SCREEN_WIDTH)/2,(2*64+SCREEN_HEIGHT)/2);
	GD.BitmapSize(BILINEAR, REPEAT, REPEAT, (SCREEN_WIDTH), (SCREEN_HEIGHT));
	GD.cmd_loadidentity();
	GD.cmd_translate(F16(480 * 1.41 / 2 - position.x),
			F16(272 * 1.41 / 2 + position.y));
	GD.cmd_rotate(3333);
	GD.cmd_translate(F16(-480 / 2), F16(-272 / 2));
	GD.cmd_setmatrix();
	GD.ColorA(255 * (clamp(f, 0.3, 1)));
	GD.Vertex2f(0, 0);
	GD.RestoreContext();
	update();

}

float BackGround::getBlendFactor() {
	float max = 30;
	float min = 10;

	return (clamp(cam.getY(), min, max) - min) / (max - min);
}

void BackGround::update() {
	position = ph->position * 4;
}
BackGround::BackGround(PhysicsObject *phin) {
	position = Vector2f();
	ph = phin;
	minPos = Vector2f();
	maxPos = Vector2f(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
}

