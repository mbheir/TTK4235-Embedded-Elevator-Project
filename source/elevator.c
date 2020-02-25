/** 
 * @file 
 * @brief Implementation file for elevator.h
 */
#include "elevator.h"

bool elevatorCheckIfOnAFloorAndUpdate(Elevator *elevator) {
	for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
		if (hardwareReadFloorSensor(floor)) {
			elevator->current_floor = floor;
			hardwareCommandFloorIndicatorOn(elevator->current_floor);
			return true;
		}
	}
	return false;
}


void elevatorUpdateOrderLights(Queue queue) {
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