#include "Accelerometer.h"


void getAcceleration(int& X, int& Y) {
	int x, y, z;
	GD.get_accel(x, y, z);

	// smoothing the acceleration to avoid noize from vibration
	gx = (gx * ACC_REACTION + x) / (ACC_REACTION + 1);
	gy = (gy * ACC_REACTION + y) / (ACC_REACTION + 1);

	X = -(gx + ACC_X_OFFSET);
	Y = -(gy + ACC_Y_OFFSET);
}

void resetAcceleration() {

	int x, y, z;
	GD.get_accel(x, y, z);
	gx = x;
	gy = y;

	for (int i = 0; i < 100; i++) {
		GD.get_accel(x, y, z);
		gx = (gx * 5 + x) / 6;
		gy = (gy * 5 + y) / 6;
		delay(1);
	}

	ACC_X_OFFSET = -gx;
	ACC_Y_OFFSET = -gy;

}

