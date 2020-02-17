#include "LightControl.h"

void lightUpdateFromQueue(bool *up_queue, bool *down_queue, bool *inside_queue) {
	for (int i =0, i<4, i++) {
		if ((*up_que+i) = true) {
			hardwareCommandOrderLight(i+1, HARDWARE_ORDER_UP, 1);
		}
		else {
			hardwareCommandOrderLight(i + 1, HARDWARE_ORDER_UP, 0);
		}
		if ((*down_que + i) = true) {
			hardwareCommandOrderLight(i + 1, HARDWARE_ORDER_DOWN, 1);
		}
		else {
			hardwareCommandOrderLight(i + 1, HARDWARE_ORDER_DOWN, 0);
		}
		if ((*inside_queue + i) = true) {
			hardwareCommandOrderLight(i + 1, HARDWARE_ORDER_INSIDE, 1);
		}
		else {
			hardwareCommandOrderLight(i + 1, HARDWARE_ORDER_INSIDE, 0);
		}
	}
	
	
}
