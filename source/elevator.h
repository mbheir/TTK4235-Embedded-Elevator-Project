/**
 * @file
 * @brief Elevator and queue struct setup, and functions directly handling with the state variables. 
 */
#ifndef ELEVATOR_H
#define ELEVATOR_H

#define ELEVATOR_INIT_FLOOR -1

#include <stdbool.h>
#include "hardware.h"


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
 * @brief A structure to hold the incoming orders. Holds three different arrays depening on where the order is from.
 */
typedef struct Queue {
    bool up[HARDWARE_NUMBER_OF_FLOORS];                 /**< upgoing orders */
    bool down[HARDWARE_NUMBER_OF_FLOORS];               /**< downgoing orders */
    bool inside[HARDWARE_NUMBER_OF_FLOORS];             /**< orders coming from inside the cab */ 
} Queue;


/**
 * @brief A structure to represent the elevators state variables.  
 */
typedef struct Elevator {
    State state;                    /**< The elevators current state. */
    int current_floor;              /**< The elevators current floor.  */ 
    bool direction_from_floor_up;   /**< Outgoing direction of the last visited floor, true is up */
    bool lights_updated;            /**< Indicates whether the order-lights have been updated for the elevator-system */
    Queue queue;                    /**< The elevators list of active orders */
} Elevator;




/**
 * @brief Checks whether the elevator is on a floor, and updates the elevators current_floor state variable.
 * 
 * @param[out] elevator     Pointer to Elevator that holds current_floor state variable
 * 
 * @return true, if on a floor. false, else
 */
bool elevatorCheckIfOnAFloorAndUpdate(Elevator *elevator);


/**
 * @brief Turns on or off light based on orders in queue
 * @param[in] queue Queue with orders
 */
void elevatorUpdateOrderLights(Queue queue);

#endif
