/**
 * @file
 * @brief Module for elevator queue setup and handling
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "hardware.h"
#include "elevator.h"



/**
 * @brief Reads all order buttons and and calls queueAddOrderToQueue for each pending order 
 *
 * @param[out] elevator     Pointer to elevator that holds the queue
 */
void queueUpdateFromButtons(Elevator *elevator);


/**
 * @brief Adds order to queue in Elevator struct
 *
 * @param[in] floor         Floor index
 * @param[in] order         Order type used to place order in up, down or inside queue
 * @param[out] elevator     Pointer to elevator that holds the queue
 */
void queueAddOrderToQueue(int floor, HardwareOrder order, Elevator *elevator);


/**
 * @brief Checks if there are any orders left in the queue
 *
 * @param[out] elevator     Pointer to elevator that holds the queue
 * 
 * @return true, if the up,down,inside queues has any order. false, if they hasn't.  
 */
bool queueCheckIfAnyOrderExist(Elevator *elevator);


/**
 * @brief Removes all orders in que for a specific floor
 *
 * @param[in] floor         Floor index
 * @param[out] elevator     Pointer to elevator that holds the queue
 */
void queueClearAllOrdersOnFloor(int floor, Elevator *elevator);


/**
 * @brief Checks if there's any orders on specific floor for all the three queues
 *
 * @param[in] floor         Floor index
 * @param[in] queue         Queue with all orders
 * 
 * @return true, on success. false, if no order was found.
 */
bool queueCheckIfAnyOrderOnFloor(int floor, Queue queue);


/**
 * @brief Clears all orders
 *
 * @param[out] elevator     Pointer to elevator that holds the queue with orders
 */
void queueClearAllOrders(Elevator *elevator);


/**
 * @brief Checks if it exists an order in the same direction, or inside the cabinette for a given floor.
 *
 * @param[in] queue         Queue with all orders
 * @param[in] current_floor Current floor for the elevator
 * @param[in] direction     Elevator heading
 * 
 * @return true, on success. false, if no order was found.
 */
bool queueCheckIfOrderInSameDirection(Queue queue, int current_floor, bool direction);


/**
 * @brief Checks if the order is the last one in the current direction
 *
 * @param[out] elevator     Pointer to elevator that holds the queue
 * 
 * @return true, on success. false, else
 */
bool queueCheckIfLastOrderInDirection(Elevator *elevator);

#endif
