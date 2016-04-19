#pragma once

#include "GD2.h"
#include "Sprite.h"
#include "arduino.h"

class Sprite
{
protected:
    unsigned char id;
    unsigned short width, height;
    unsigned char cells;
    
public:

    Sprite(unsigned char BitMapHandle, unsigned short imageWidth, unsigned short imageHeight, unsigned char cells);
    virtual ~Sprite();
    void render(int x, int y, unsigned short angle, unsigned short scale, unsigned char cell);//draws a sprite at x,y acording to its center, rotated around the center.

};