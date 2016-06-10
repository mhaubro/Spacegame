
#include "SpriteTemplate.h"
#include "GD2.h"
#include "arduino.h"
#include "Graphics.h"

#define SQRT2 1.41

SpriteTemplate::SpriteTemplate(unsigned char BitMapHandle, unsigned short imageWidth, unsigned short imageHeight, unsigned char cell)
: 	id(BitMapHandle),
	width(imageWidth),
	height(imageHeight),
	cell(cell),
	offsetX((imageWidth*SQRT2)/(UNIT*2)),
	offsetY((imageHeight*SQRT2)/(UNIT*2))
{
    
}

SpriteTemplate::~SpriteTemplate()
{
    
}

void SpriteTemplate::render(const float x, const float y, const float angle, const float scale)
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

void SpriteTemplate::render(const Vector2f pos, const float angle, const float scale){
	render(pos.x,pos.y,angle,scale);
}
