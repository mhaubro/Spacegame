#pragma once

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
