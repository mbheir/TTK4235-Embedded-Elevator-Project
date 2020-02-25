/**
 * @file
 * @brief Function for updating all lights based on orders in queue
 */

#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H
#include <stdbool.h>
#include "hardware.h"
#include "queue.h"

/**
 * @brief Turns on or off light based on orders in queue
 * @param[in] queue Queue with orders
 */
void lightUpdateFromQueue(Queue queue);

#endif
