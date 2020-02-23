/**
 * @file
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "hardware.h"
//#include "elevator.h"


typedef enum {
    INIT, 
    STANDBY, 
    DOORS_OPEN, 
    GOING_UP, 
    GOING_DOWN, 
    EMERGENCY
} State;


typedef struct Queue {
    bool up[4];
    bool down[4];
    bool inside[4];
} Queue;



typedef struct Elevator {
    State state;    
    int current_floor; //starting from 0
    bool direction_from_floor_up; //true is up
    bool lights_updated;    
    Queue queue;
}  Elevator;


void queueUpdateFromButtons(Elevator *elevator);

void queueAddOrderToQueue(int floor, HardwareOrder order, Elevator *elevator);

bool queueCheckIfAnyOrderExist(Elevator *elevator);

void queueClearAllOrdersOnFloor(int floor, Elevator *elevator); 

bool queueCheckIfAnyOrderOnFloor(int floor, Queue queue);

void queueClearAllOrders(Elevator *elevator);

bool queueCheckIfOrderInSameDirection(Queue queue, int current_floor, int direction);

bool queueLastOrderInDirection(Elevator *elevator);

#endif
