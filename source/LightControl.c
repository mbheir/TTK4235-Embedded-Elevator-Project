#include "LightControl.h"

void lightUpdateFromQueue(bool up_queue[], bool down_queue[], bool inside_queue[]) {
	for (int i =0, i < HARDWARE_NUMBER_OF_FLOORS, i++) {
		if (up_queue[i]) {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_UP, 1);
		}
		else {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_UP, 0);
		}
		if (down_queue[i]) {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_DOWN, 1);
		}
		else {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_DOWN, 0);
		}
		if (down_queue[i]) {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_INSIDE, 1);
		}
		else {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_INSIDE, 0);
		}
	}
}

