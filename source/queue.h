/**
 * @file
 * @brief Module for elevator queue setup and handling
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

/**
 * @brief Reads all order buttons and and calls queueAddOrderToQueue for each pending order 
 *
 * @param[out] elevator Pointer to elevator that holds the queue
 */
void queueUpdateFromButtons(Elevator *elevator);

/**
 * @brief Adds order to queue in Elevator struct
 *
 * @param[in] floor Floor index
 * @param[in] order Order type used to place order in up, down or inside queue
 * @param[out] elevator Pointer to elevator that holds the queue
 */
void queueAddOrderToQueue(int floor, HardwareOrder order, Elevator *elevator);

/**
 * @brief Checks if there are any orders left in the queue
 *
 * @param[out] elevator Pointer to elevator that holds the queue
 */
bool queueCheckIfAnyOrderExist(Elevator *elevator);


/**
 * @brief Removes all orders in que for a specific floor
 *
 * @param[in] floor Floor index
 * @param[out] elevator Pointer to elevator that holds the queue
 */
void queueClearAllOrdersOnFloor(int floor, Elevator *elevator);


/**
 * @brief Checks if there's any orders on specific floor
 *
 * @param[in] floor Floor index
 * @param[in] queue Queue with all orders
 */
bool queueCheckIfAnyOrderOnFloor(int floor, Queue queue);

/**
 * @brief Clears all orders
 *
 * @param[out] elevator Pointer to elevator that holds the queue with orders
 */
void queueClearAllOrders(Elevator *elevator);

/**
 * @brief Checks if an order is the same direction as the elevator is heading
 *
 * @param[in] queue Queue with all orders
 * @param[in] current_floor Current floor for the elevator
 * @param[in] direction Elevator heading
 */
bool queueCheckIfOrderInSameDirection(Queue queue, int current_floor, int direction);

/**
 * @brief Checks if the order is the last one in the current direction
 *
 * @param[out] elevator Pointer to elevator that holds the queue
 */
bool queueCheckIfLastOrderInDirection(Elevator *elevator);

#endif
