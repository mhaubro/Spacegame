//Author: MH

#include "Button.h"

Button::Button(const PinName pin)
{
    input = new DigitalIn(pin);
    //input->mode(PullUp);
}


Button::~Button()
{
    if (input)
        delete input;
}

bool Button::isPressed()
{
    return (input->read() == 1);
}

