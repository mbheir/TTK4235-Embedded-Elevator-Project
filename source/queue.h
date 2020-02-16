/**
 * @file
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "hardware.h"


typedef struct Queue {
    int up[4];
    int down[4];
    int inside[4];
} Queue;


void queueUpdateFromButtons(int *buttons);

void queueRemoveElement(int *queue, int floor);

bool queueCheckIfInFloor(Queue queue, int code, int floor);



#endif