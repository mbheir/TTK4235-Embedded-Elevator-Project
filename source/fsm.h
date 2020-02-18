/**
 * @file
 * @brief header file for Finite State Machine
 */
#ifndef FSM_H
#define FSM_H1

#include <stdio.h>
#include <time.h>
#include "hardware.h"
#include "LightControl.h"
#include "queue.h"

void fsmInit(Elevator *elevator);

void fsmStandby(Elevator *elevator);

void fsmDoorsOpen(Elevator *elevator);

void fsmGoingUp(Elevator *elevator);

void fsmGoingDown(Elevator *elevator);

void fsmEmergency(Elevator *elevator);

#endif
