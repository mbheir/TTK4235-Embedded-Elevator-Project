/**
 * @file
 */

#include "fsm.h"

void fsmInit(Elevator *elevator) {
    printf("Entering state INIT\n");

    queueClearAllOrders(elevator);
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
    
    while (true) {

        queueUpdateFromButtons(elevator);

        if (queueCheckIfAnyOrderExist(elevator)) {
            lightUpdateFromQueue(elevator->queue.up,elevator->queue.down,elevator->queue.inside);


            if (queueCheckIfAnyOrderOnFloor(elevator->current_floor,elevator->queue)) {
                elevator->state = DOORS_OPEN;
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

    while (diff_time < 3) { 
        queueUpdateFromButtons(elevator);
        lightUpdateFromQueue(elevator->queue.up,elevator->queue.down,elevator->queue.inside);



        time(&end_time);
        diff_time = difftime(end_time,start_time);
    }

    hardwareCommandDoorOpen(0);
    queueClearAllOrdersOnFloor(elevator->current_floor,elevator);
    elevator->state = STANDBY;
}


void fsmGoingUp(Elevator *elevator) {
    hardwareCommandMovement(HARDWARE_MOVEMENT_UP);

    while (true){
        queueUpdateFromButtons(elevator);
        lightUpdateFromQueue(elevator->queue.up,elevator->queue.down,elevator->queue.inside);

        if (checkAndUpdateFloor(elevator) && (elevator->queue.up[elevator->current_floor] || elevator->queue.inside[elevator->current_floor])) {
            break;
        }
    }
    elevator->state = STANDBY;
}


void fsmGoingDown(Elevator *elevator) {
    hardwareCommandMovement(HARDWARE_MOVEMENT_DOWN);

    while (true){
        queueUpdateFromButtons(elevator);
        lightUpdateFromQueue(elevator->queue.up,elevator->queue.down,elevator->queue.inside);

        if (checkAndUpdateFloor(elevator) && (elevator->queue.down[elevator->current_floor] || elevator->queue.inside[elevator->current_floor])) {
            break;
        }
    }
    elevator->state = STANDBY;
}
