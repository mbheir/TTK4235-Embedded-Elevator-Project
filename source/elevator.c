#include "elevator.h"

bool checkAndUpdateFloor(Elevator *elevator) {
	for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
		if (hardwareReadFloorSensor(floor)) {
			elevator->current_floor = floor;
			hardwareCommandFloorIndicatorOn(elevator->current_floor);
			return true;
		}
	}
	return false;
}