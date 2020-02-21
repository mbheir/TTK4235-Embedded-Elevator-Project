#include "queue.h"

void queueUpdateFromButtons(Elevator *elevator) {

    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; ++floor) {
        for (HardwareOrder order = HARDWARE_ORDER_UP; order <= HARDWARE_ORDER_DOWN; ++order) {
            if (hardwareReadOrder(floor,order)) {
                queueAddOrderToQueue(floor,order,elevator);
				elevator->lights_updated = false;
            }   
        }
    }
}

void queueAddOrderToQueue(int floor, HardwareOrder order, Elevator *elevator) {
    switch (order)
    {
    case HARDWARE_ORDER_UP:
        elevator->queue.up[floor] = true;
        break;
    case HARDWARE_ORDER_DOWN:
        elevator->queue.down[floor] = true;
        break;
    case HARDWARE_ORDER_INSIDE:
        elevator->queue.inside[floor] = true;
        break;
	}
}

bool queueCheckIfAnyOrderExist(Elevator *elevator){
	for(unsigned int i=0; i<HARDWARE_NUMBER_OF_FLOORS;i++){
		if(elevator->queue.up[i] || elevator->queue.down[i] || elevator->queue.inside[i]){
			return true;
		}
	}
	return false;
}


bool queueCheckIfAnyOrderOnFloor(int floor, Queue queue) {
	return (queue.down[floor] || queue.up[floor] || queue.inside[floor]);
}

void queueClearAllOrdersOnFloor(int floor, Elevator *elevator){
	elevator->queue.up[floor]=false;
	elevator->queue.down[floor]=false;
	elevator->queue.inside[floor]=false;
	elevator->lights_updated = false;
}

void queueClearAllOrders(Elevator *elevator) {
	for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
		queueClearAllOrdersOnFloor(floor,elevator);
	}
}


void queueRemoveElementFromQueue(bool queue[], int floor){  //NB!! Tror ikke denne kommer til å funke !
	queue[floor]=false;
}

bool queueCheckIfOrderInSameDirection(Queue queue, int current_floor, int direction) {
	if (direction) {
		for (int floor=current_floor+1; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
			if (queue.down[floor] || queue.up[floor] || queue.inside[floor]) {
				return true;
			}
		}
		return false;
	}
	else {
		for (int floor=current_floor-1; floor >= 0; floor--) {
			if (queue.down[floor] || queue.up[floor] || queue.inside[floor]) {
				return true;
			}
		}
		return false;
	}
	
}

bool queueLastOrderInDirection(Elevator *elevator){
	if (elevator->last_direction_up){
		for (unsigned int i=(elevator->current_floor+1); i<HARDWARE_NUMBER_OF_FLOORS;i++){
			if (queueCheckIfAnyOrderOnFloor(i,elevator->queue)){
				return false;	
			}
		}
	}
	else{
		for(unsigned int i=0; i<(elevator->current_floor);i++){
			if(queueCheckIfAnyOrderOnFloor(i,elevator->queue)){
				return false;	
			}
		}
	}
	return true;
}
