/**
 * @file
 * @brief Header file for the Finite State Machine. 
 */
#ifndef FSM_H
#define FSM_H1

#include <stdio.h>
#include <time.h>

#include "queue.h"

/**
 * @brief Initial state. Launched at startup and initializes the machine. 
 * @param elevator      Pointer to Elevator that holds all the state variables
 */
void fsmInit(Elevator *elevator);


/**
 * @brief Standby state. Taking orders and pushing the elevator to other states
 * @param elevator      Pointer to Elevator that holds all the state variables
 */
void fsmStandby(Elevator *elevator);


/**
 * @brief DoorsOpen state. Handles the procedure of visiting a floor. 
 * @param elevator      Pointer to Elevator that holds all the state variables
 */
void fsmDoorsOpen(Elevator *elevator);


/**
 * @brief GoingUp state. Handles the necessary procedures when the elevator is moving up.
 * @param elevator      Pointer to Elevator that holds all the state variables
 */
void fsmGoingUp(Elevator *elevator);


/**
 * @brief GoingDown state. Handles the necessary procedures when the elevator is moving down.
 * @param elevator      Pointer to Elevator that holds all the state variables
 */
void fsmGoingDown(Elevator *elevator);


/**
 * @brief Emergency state. Handles the necessary procedures when the stop button is pressed. 
 * @param elevator      Pointer to Elevator that holds the elevators state variables
 */
void fsmEmergency(Elevator *elevator);

#endif
