#include <stdio.h>
#include <stdlib.h>

#include "hardware.h"
#include "elevator.h"
#include "fsm.h"
#include "queue.h"
#include "LightControl.h"

int main(){
    int error = hardwareInit();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to EXIT\n");
    

    Elevator *elevator = (Elevator*)malloc(sizeof(Elevator));

    elevator->state = INIT;


    while(true){

        
        switch (elevator->state)
        {

        case INIT:
            fsmInit(elevator);
            break;
        case STANDBY:
            fsmStandby(elevator); 
            break;
        case DOORS_OPEN:
            fsmDoorsOpen(elevator);
            break;
        case GOING_UP:
            fsmGoingUp(elevator);
            break;
        case GOING_DOWN:
            fsmGoingDown(elevator);
            break;
        case EMERGENCY:
	    fsmEmergency(elevator);
            break;
        }

    }

    return 0;
}
