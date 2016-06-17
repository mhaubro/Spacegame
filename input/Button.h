//Author: MH

#ifndef BUTTON_H_
#define BUTTON_H_

#include "mbed.h"

class Button
{
protected:
    DigitalIn* input;
    
public:
    Button(const PinName pinIn);
    virtual ~Button();
    bool isPressed();

};

#endif
