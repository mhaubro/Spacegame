#ifndef UI_H_
#define UI_H_

#include "button.h"

class UI
{
protected:
	Button * button1;
	Button * button2;
	Button * button3;
	Button * button4;
    
public:
    UI();
    void render();
};

#endif
