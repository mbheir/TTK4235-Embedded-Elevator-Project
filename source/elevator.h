/**
 * @file
 * @brief Elevator object
 */
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <stdbool.h>
#include "queue.h"

/**
 * @brief An enum to represent the different states the elevator can achieve.
 */
typedef enum {
    INIT, 
    STANDBY, 
    DOORS_OPEN, 
    GOING_UP, 
    GOING_DOWN, 
    EMERGENCY
} State;

/**
 * @brief A structure to represent the queue. Holds three different arrays depening on where the order is from.
 */
typedef struct Queue {
    bool up[4];                 /** < upgoing orders */
    bool down[4];               /** < downgoing orders */
    bool inside[4];             /** < orders coming from inside the cab */ 
} Queue;


/**
 * @brief A structure to represent the elevators state variables.  
 */
typedef struct Elevator {
    State state;                    /** < The elevators current state. */
    int current_floor;              /** < The elevators current floor. -1 indicates uninitialized */ 
    bool direction_from_floor_up;   /** < Outgoing direction of the last visited floor, true is up */
    bool lights_updated;            /** < Indicates whether the order-lights have been updated for the elevator-system */
    Queue queue;                    /** < The elevators order queue */
}  Elevator;


bool checkAndUpdateFloor(Elevator *elevator);

#endif
