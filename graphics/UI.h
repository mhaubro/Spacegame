#ifndef UI_H_
#define UI_H_

#include "button.h"
#include "myassets.h"
#include "SpriteTemplate.h"

class UI
{
protected:
    
	SpriteTemplate * youDied;

public:
    UI();
    void render();

};

#endif
