#ifndef UI_H_
#define UI_H_

#include "button.h"
#include "myassets.h"
#include "SpriteTemplate.h"

class UI
{
protected:
    
	SpriteTemplate * youDied = new SpriteTemplate(YOU_DIED_HANDLE, 60, 33, 0);


public:
    UI();
    void render();
};

#endif
