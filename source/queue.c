#include "queue.h"

void queueUpdateFromButtons(Elevator *elevator) {

    for (int floor; floor < HARDWARE_NUMBER_OF_FLOORS; ++floor) {
        for (HardwareOrder order = HARDWARE_ORDER_UP; order != HARDWARE_ORDER_DOWN; ++order) {
            if (hardwareReadOrder(floor,order)) {
                queueAddOrderToQueue(floor,order, elevator);
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

void queueClearAllOrdersOnFloor(int floor, Elevator *elevator){
	elevator->queue.up[floor]=false;
	elevator->queue.down[floor]=false;
	elevator->queue.inside[floor]=false;
}


void queueRemoveElementFromQueue(bool queue[], int floor){
	queue[floor]=false;
}
