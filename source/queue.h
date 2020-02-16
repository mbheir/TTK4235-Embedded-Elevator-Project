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





#endif