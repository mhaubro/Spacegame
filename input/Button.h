#pragma once

#include "mbed.h"

class Button
{
protected:
    DigitalIn* input;
    
public:
    Button(const PinName pin);
    virtual ~Button();
    bool isPressed();

};