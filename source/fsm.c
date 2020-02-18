/**
 * @file
 */

#include "fsm.h"

void fsmInit(Elevator *elevator) {
    printf("Entering state INIT\n");

    queueClearAllOrders(elevator);
    elevator->direction = false;
    elevator->lights_updated = false;
    hardwareCommandMovement(HARDWARE_MOVEMENT_DOWN);

    while (true) {
        if (checkAndUpdateFloor(elevator)) {
            hardwareCommandMovement(HARDWARE_MOVEMENT_STOP);
            break;
        }
    }

    elevator->state = STANDBY;
}


void fsmStandby(Elevator *elevator) {
    printf("Entering state STANDBY\n");

    while (elevator->state == STANDBY) {
	if (hardwareReadStopSignal() == 1){
		elevator->state = EMERGENCY;
		break;
	}
        queueUpdateFromButtons(elevator);
	
        if (!elevator->lights_updated) {
            lightUpdateFromQueue(elevator->queue.up,elevator->queue.down,elevator->queue.inside);
            elevator->lights_updated = true;
        }

        if (queueCheckIfAnyOrderExist(elevator)) {


            if (hardwareReadFloorSensor(elevator->current_floor) && (queueCheckIfAnyOrderOnFloor(elevator->current_floor,elevator->queue))) {
                elevator->state = DOORS_OPEN;
                break;
            }
            if (queueCheckIfOrderInSameDirection(elevator->queue,elevator->current_floor,elevator->direction)) {
                if (elevator->direction) elevator->state = GOING_UP;
                else elevator->state = GOING_DOWN;
                break;
            }
            else {
                if (elevator->direction) elevator->state = GOING_DOWN;
                else elevator->state = GOING_UP;
                break;
            }
        }
    }
}

void fsmDoorsOpen(Elevator *elevator) {
    printf("Entering state DOORS_OPEN\n");

    time_t start_time, end_time;
    double diff_time = 0;
    time(&start_time);

    hardwareCommandDoorOpen(1);

    while (true) { 
        if (hardwareReadStopSignal() == 1){
		elevator->state = EMERGENCY;
		break;
	}
	queueUpdateFromButtons(elevator);
        if (!elevator->lights_updated) {
            lightUpdateFromQueue(elevator->queue.up,elevator->queue.down,elevator->queue.inside);
            elevator->lights_updated = true;
        }
	if (hardwareReadObstructionSignal() == 1){
		time(&start_time);
	}


        time(&end_time);
        diff_time = difftime(end_time,start_time);
	if(hardwareReadStopSignal() == 1){
		elevator->state = EMERGENCY;
		hardwareCommandDoorOpen(0);
	        break;	
	}
	if(diff_time>3){
		elevator->state = STANDBY;
		 hardwareCommandDoorOpen(0);
		break;	
	}
    }
    queueClearAllOrdersOnFloor(elevator->current_floor,elevator);
}


void fsmGoingUp(Elevator *elevator) {
    printf("Entering state GOING_UP\n");

    elevator->direction = true;
    hardwareCommandMovement(HARDWARE_MOVEMENT_UP);

    while (true){
	if (hardwareReadStopSignal() == 1){
		elevator->state = EMERGENCY;
		break;
	}	    
        queueUpdateFromButtons(elevator);
        if (!elevator->lights_updated) {
            lightUpdateFromQueue(elevator->queue.up,elevator->queue.down,elevator->queue.inside);
            elevator->lights_updated = true;
        }

        if (checkAndUpdateFloor(elevator) && ((elevator->queue.up[elevator->current_floor] || elevator->queue.inside[elevator->current_floor]) || (queueLastOrderInDirection(elevator) && elevator->queue.down[elevator->current_floor]))) {
		elevator->state = STANDBY;
	      	break;
	}
    }
    hardwareCommandMovement(HARDWARE_MOVEMENT_STOP);
}


void fsmGoingDown(Elevator *elevator) {
    printf("Entering state GOING_DOWN\n");

    elevator->direction = false;
    hardwareCommandMovement(HARDWARE_MOVEMENT_DOWN);

    while (true){
	if (hardwareReadStopSignal() == 1){
		elevator->state = EMERGENCY;
		break;
	}
        queueUpdateFromButtons(elevator);
        if (!elevator->lights_updated) {
            lightUpdateFromQueue(elevator->queue.up,elevator->queue.down,elevator->queue.inside);
            elevator->lights_updated = true;
        }

        if (checkAndUpdateFloor(elevator) && ((elevator->queue.down[elevator->current_floor] || elevator->queue.inside[elevator->current_floor]) || (queueLastOrderInDirection(elevator) && elevator->queue.up[elevator->current_floor]))) {
		elevator->state = STANDBY;
	   	break;
        }
    }
    hardwareCommandMovement(HARDWARE_MOVEMENT_STOP);

}

void fsmEmergency(Elevator *elevator){
	printf("Entering state EMERGENCY\n");

	if(hardwareReadFloorSensor(elevator->current_floor)){
		elevator->state = DOORS_OPEN;
	}
	else{
		elevator->state = STANDBY;
	}
	queueClearAllOrders(elevator);
}
