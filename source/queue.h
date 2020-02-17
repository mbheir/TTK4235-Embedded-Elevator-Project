/**
 * @file
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "hardware.h"
//#include "elevator.h"


typedef enum State { 
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
    int current_floor;
    bool floor_sensor_triggered;
    bool emergency_stop;
    bool door_open;
    bool last_direction;
    Queue queue;
}  Elevator;


void queueUpdateFromButtons(Elevator *elevator);

void queueAddOrderToQueue(int floor, HardwareOrder order, Elevator *elevator);

bool queueOrderInCurrentDirection(int order_floor, int current_floor, bool last_direction);

bool queueOrderExist(Elevator *elevator);

void queueClearAllOrdersOnFloor(int floor, Elevator *elevator);

void queueRemoveElementFromQueue(array *queue int floor);

bool queueFloorInQueue(array *queue, array *queue2, int floor);





#endif
