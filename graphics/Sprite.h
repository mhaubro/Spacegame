#pragma once

#include "GD2.h"
#include "Sprite.h"
#include "arduino.h"
#include "Graphics.h"

class Sprite
{
protected:
    const unsigned char id;
    const unsigned short width, height;
    const unsigned char cells;
    
    const float offsetX, offsetY;

public:

    Sprite(unsigned char BitMapHandle, unsigned short imageWidth, unsigned short imageHeight, unsigned char cells);
    virtual ~Sprite();
    void render(const float x, const float y, const float angle, const float scale, unsigned char cell);//draws a sprite at x,y acording to its center, rotated around the center.

};
