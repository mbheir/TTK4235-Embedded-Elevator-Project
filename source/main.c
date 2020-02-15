#include <stdio.h>
#include <stdlib.h>

#include "hardware.h"
#include "elevator.h"
#include "fsm.h"
#include "queue.h"


void exampleProgramTick() { //jalla

        if(hardwareReadFloorSensor(0)){
            hardwareCommandMovement(HARDWARE_MOVEMENT_UP);
        }
        if(hardwareReadFloorSensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardwareCommandMovement(HARDWARE_MOVEMENT_DOWN);
        }
}


int main(){

    int error = hardwareInit();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    hardwareCommandMovement(HARDWARE_MOVEMENT_UP);



    while(true){

        
        if (true) {
            exampleProgramTick();
        }




    }
}