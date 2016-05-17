
#include "Sprite.h"
#include "GD2.h"
#include "arduino.h"
#include "Graphics.h"

#define SQRT2 1.41

Sprite::Sprite(unsigned char BitMapHandle, unsigned short imageWidth, unsigned short imageHeight, unsigned char cells)
: 	id(BitMapHandle),
	width(imageWidth),
	height(imageHeight),
	cells(cells),
	offsetX((imageWidth*SQRT2)/(UNIT*2)),
	offsetY((imageHeight*SQRT2)/(UNIT*2))
{
    
}

Sprite::~Sprite()
{
    
}

void Sprite::render(const float x, const float y, const float angle, const float scale, const unsigned char cell)
{
    GD.BitmapHandle(id);
    GD.Cell(cell);
    GD.BitmapSize(BILINEAR,BORDER,BORDER,scale*width*SQRT2,scale*height*SQRT2);
    GD.cmd_loadidentity();
    GD.cmd_translate(F16(scale*width*SQRT2/2),F16(scale*height*SQRT2/2));
    GD.cmd_rotate(FURMANS(angle));
    GD.cmd_translate(F16(-scale*width/2),F16(-scale*height/2));
    GD.cmd_scale(F16(scale),F16(scale));
    GD.cmd_setmatrix();
    cam.Vertex2f(x-offsetX*scale,y+offsetY*scale);
}
