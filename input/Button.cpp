#include "Button.h"

Button::Button(const PinName pin)
{
    input = new DigitalIn(pin);
}

Button::~Button()
{
    if (input)
        delete input;
}

bool Button::isPressed()
{
    return (*input == 1);
}

