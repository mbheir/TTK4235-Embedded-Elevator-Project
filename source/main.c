#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"

int main(){
    int error = hardwareInit();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    hardwareCommandMovement(HARDWARE_MOVEMENT_UP);

    while(1){
        if(hardwareReadStopSignal()){
            hardwareCommandMovement(HARDWARE_MOVEMENT_STOP);
            break;
        }

        if(hardwareReadFloorSensor(0)){
            hardwareCommandMovement(HARDWARE_MOVEMENT_UP);
        }
        if(hardwareReadFloorSensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardwareCommandMovement(HARDWARE_MOVEMENT_DOWN);
        }
    }
}