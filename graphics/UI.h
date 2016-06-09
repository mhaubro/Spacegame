#ifndef UI_H_
#define UI_H_

#include "button.h"
#include "myassets.h"
#include "SpriteTemplate.h"

class UI
{
protected:
	Button * button1;
	Button * button2;
	Button * button3;
	Button * button4;
    
	SpriteTemplate * youDied = new SpriteTemplate(YOU_DIED_HANDLE, 60, 33, 0);


public:
    UI();
    void render();
};

#endif
