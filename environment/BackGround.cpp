#include "BackGround.h"
#include "GD2.h"
#include "utils.h"
#include "myassets.h"
#include "graphics.h"
#include "sprite.h"

void BackGround::render(){
	GD.Begin(BITMAPS);

	GD.BitmapHandle(RANDOMDOTS_HANDLE);
	GD.Cell(RANDOMDOTS_CELLS-1);
	//GD.BitmapSize(BILINEAR,REPEAT,REPEAT,(2*64+SCREEN_WIDTH)/2,(2*64+SCREEN_HEIGHT)/2);
	GD.BitmapSize(BILINEAR,REPEAT,REPEAT,(SCREEN_WIDTH),(SCREEN_HEIGHT));

	GD.cmd_loadidentity();
	GD.cmd_translate(F16(480*1.41/2-position.x),F16(272*1.41/2+position.y));
    GD.cmd_rotate(3333);

    GD.cmd_translate(F16(-480/2),F16(-272/2));

   //GD.cmd_scale(F16(2),F16(2));

    GD.cmd_setmatrix();

	//cam.Vertex2f(position);
	//GD.Vertex2f(-64*UNIT + position.x, -64*UNIT+position.y);
	//GD.Vertex2f((-64+(2*64+SCREEN_WIDTH)/2)*UNIT+ position.x, -64*UNIT+position.y);
	//GD.Vertex2f(-64*UNIT+ position.x, (-64+(2*64+SCREEN_HEIGHT)/2)*UNIT+position.y);
	//GD.Vertex2f((-64+(2*64+SCREEN_WIDTH)/2)*UNIT+ position.x, (-64+(2*64+SCREEN_HEIGHT)/2)*UNIT+position.y);
    GD.Vertex2f(0, 0);
	GD.RestoreContext();
	//Sprite sky = Sprite(NIGHTSKY_HANDLE, 64, 64,NIGHTSKY_CELLS);
	//sky.render(3.0f, 3.0f, 0.0f, 1.0f, NIGHTSKY_CELLS);
	update();

}

void BackGround::update(){
	position = ph->position*4;
}
BackGround::BackGround(PhysicsObject *phin){
	position = Vector2f();
	ph = phin;
	minPos = Vector2f();
	maxPos = Vector2f(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
}


