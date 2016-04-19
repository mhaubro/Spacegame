
#include "Sprite.h"

Sprite::Sprite(unsigned char BitMapHandle, unsigned short imageWidth, unsigned short imageHeight, unsigned char cells)
: id(BitMapHandle), width(imageWidth*2), height(imageHeight*2), cells(cells)
{
    
}

Sprite::~Sprite()
{
    
}

void Sprite::render(const int x, const int y, const unsigned short angle, const unsigned short scale, const unsigned char cell)
{
    GD.BitmapHandle(id);
    GD.Cell(cell);
    GD.BitmapSize(BILINEAR,BORDER,BORDER,width,height);
    GD.cmd_loadidentity();
    GD.cmd_translate(F16(width/2),F16(height/2));//Sørger for, at rotation er omkring centrum.
    GD.cmd_rotate(angle);
    GD.cmd_translate(F16(-width/4),F16(-height/4));
    GD.cmd_setmatrix();
    GD.Vertex2f((x-width/2)*16,(y-height/2)*16);
}
