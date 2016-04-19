#pragma once

#include "GD2.h"


#define ACC_REACTION 5

static int ACC_X_OFFSET = 0; //-2
static int ACC_Y_OFFSET = 0; //-24

static int gx = 0, gy = 0;

void resetAcceleration();
void getAcceleration(int& X, int& Y);

