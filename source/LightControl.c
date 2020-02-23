#include "LightControl.h"

void lightUpdateFromQueue(Queue queue) {
	for (int i =0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
		if (queue.up[i]) {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_UP, 1);
		}
		else {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_UP, 0);
		}
		if (queue.down[i]) {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_DOWN, 1);
		}
		else {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_DOWN, 0);
		}
		if (queue.inside[i]) {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_INSIDE, 1);
		}
		else {
			hardwareCommandOrderLight(i, HARDWARE_ORDER_INSIDE, 0);
		}
	}
}
