/**
 * @file
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "hardware.h"
#include "elevator.h"


void queueUpdateFromButtons(Elevator *elevator);

void queueAddOrderToQueue(int floor, HardwareOrder order, Elevator *elevator);

bool queueOrderInCurrentDirection(int order_floor, int current_floor, bool last_direction);

bool queueOrderExist(Elevator *elevator);

void queueClearAllOrdersOnFloor(int floor, Elevator *elevator);

void queueRemoveElementFromQueue(array *queue int floor);

bool queueFloorInQueue(array *queue, array *queue2, int floor);





#endif
