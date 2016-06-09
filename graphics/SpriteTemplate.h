#ifndef SPRITE_H_
#define SPRITE_H_

#include "Vector2f.h"

class SpriteTemplate
{
protected:
    const unsigned char id;
    const unsigned short width, height;
    const unsigned char cell;
    
    const float offsetX, offsetY;

public:

    SpriteTemplate(unsigned char BitMapHandle, unsigned short imageWidth, unsigned short imageHeight, unsigned char cell);
    virtual ~SpriteTemplate();
    void render(const float x, const float y, const float angle, const float scale);//draws a sprite at x,y acording to its center, rotated around the center.
    void render(const Vector2f pos, const float angle, const float scale);
};

#endif
