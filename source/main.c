#include <stdio.h>
#include <stdlib.h>

#include "hardware.h"
#include "elevator.h"
#include "fsm.h"
#include "queue.h"

int main(){
    int error = hardwareInit();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    hardwareCommandMovement(HARDWARE_MOVEMENT_UP);


    State state = STANDBY;

    while(true){

        
        switch (state)
        {
        case STANDBY:
            fsmStandby(); 
            break;
        case DOORS_OPEN:
            break;
        case GOING_UP:
            break;
        case GOING_DOWN:
            break;
        case EMERGENCY:
            break;
        }

    }

    return 0;
}
