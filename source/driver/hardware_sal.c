#include "hardware.h"
#include "channels.h"
#include "io.h"

#include <stdlib.h>

static int hardwareLegalFloor(int floor, HardwareOrder order_type){
    int lower_floor = 0;
    int upper_floor = HARDWARE_NUMBER_OF_FLOORS - 1;

    if(floor < lower_floor || floor > upper_floor){
        return 0;
    }

    if(floor == lower_floor && order_type == HARDWARE_ORDER_DOWN){
        return 0;
    }

    if(floor == upper_floor && order_type == HARDWARE_ORDER_UP){
        return 0;
    }

    return 1;
}

static int hardwareOrderTypeBit(HardwareOrder order_type){
    int type_bit;

    switch(order_type){
        case HARDWARE_ORDER_UP:
            type_bit = 0;
            break;

        case HARDWARE_ORDER_INSIDE:
            type_bit = 2;
            break;

        case HARDWARE_ORDER_DOWN:
            type_bit = 1;
            break;
    }

    return type_bit;
}

int hardwareInit(){
    if(!io_init()){
        return 1;
    }

    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(i != 0){
            hardwareCommandOrderLight(HARDWARE_ORDER_DOWN, i, 0);
        }

        if(i != HARDWARE_NUMBER_OF_FLOORS - 1){
            hardwareCommandOrderLight(HARDWARE_ORDER_UP, i, 0);
        }

        hardwareCommandOrderLight(HARDWARE_ORDER_INSIDE, i, 0);
    }

    hardwareCommandStopLight(0);
    hardwareCommandDoorOpen(0);
    hardwareCommandFloorIndicatorOn(0);

    return 0;
}

void hardwareCommandMovement(HardwareMovement movement){
    switch(movement){
        case HARDWARE_MOVEMENT_UP:
            io_clear_bit(MOTORDIR);
            io_write_analog(MOTOR, 2800);
            break;

        case HARDWARE_MOVEMENT_STOP:
            io_write_analog(MOTOR, 0);
            break;

        case HARDWARE_ORDER_DOWN:
            io_set_bit(MOTORDIR);
            io_write_analog(MOTOR, 2800);
            break;
    }
}

int hardwareReadStopSignal(){
    return io_read_bit(STOP);
}

int hardwareReadObstructionSignal(){
    return io_read_bit(OBSTRUCTION);
}

int hardwareReadFloorSensor(int floor){
    int floor_bit;
    switch(floor){
        case 0:
            floor_bit = SENSOR_FLOOR1;
            break;

        case 1:
            floor_bit = SENSOR_FLOOR2;
            break;

        case 2:
            floor_bit = SENSOR_FLOOR3;
            break;

        case 3:
            floor_bit = SENSOR_FLOOR4;
            break;

        default:
            return 0;
    }

    return io_read_bit(floor_bit);
}

int hardwareReadOrder(int floor, HardwareOrder order_type){
    if(!hardwareLegalFloor(floor, order_type)){
        return 0;
    }

    static const int order_bit_lookup[][3] = {
        {BUTTON_UP1, BUTTON_DOWN1, BUTTON_COMMAND1},
        {BUTTON_UP2, BUTTON_DOWN2, BUTTON_COMMAND2},
        {BUTTON_UP3, BUTTON_DOWN3, BUTTON_COMMAND3},
        {BUTTON_UP4, BUTTON_DOWN4, BUTTON_COMMAND4}
    };

    int type_bit = hardwareOrderTypeBit(order_type);

    return io_read_bit(order_bit_lookup[floor][type_bit]);
}

void hardwareCommandDoorOpen(int door_open){
    if(door_open){
        io_set_bit(LIGHT_DOOR_OPEN);
    }
    else{
        io_clear_bit(LIGHT_DOOR_OPEN);
    }
}

void hardwareCommandFloorIndicatorOn(int floor){
    if(floor & 0x02){
        io_set_bit(LIGHT_FLOOR_IND1);
    }
    else{
        io_clear_bit(LIGHT_FLOOR_IND1);
    }

    if(floor & 0x01){
        io_set_bit(LIGHT_FLOOR_IND2);
    }
    else{
        io_clear_bit(LIGHT_FLOOR_IND2);
    }
}

void hardwareCommandStopLight(int on){
    if(on){
        io_set_bit(LIGHT_STOP);
    }
    else{
        io_clear_bit(LIGHT_STOP);
    }
}

void hardwareCommandOrderLight(int floor, HardwareOrder order_type, int on){
    if(!hardwareLegalFloor(floor, order_type)){
        return;
    }

    static const int light_bit_lookup[][3] = {
        {LIGHT_UP1, LIGHT_DOWN1, LIGHT_COMMAND1},
        {LIGHT_UP2, LIGHT_DOWN2, LIGHT_COMMAND2},
        {LIGHT_UP3, LIGHT_DOWN3, LIGHT_COMMAND3},
        {LIGHT_UP4, LIGHT_DOWN4, LIGHT_COMMAND4}
    };

    int type_bit = hardwareOrderTypeBit(order_type);

    if(on){
        io_set_bit(light_bit_lookup[floor][type_bit]);
    }
    else{
        io_clear_bit(light_bit_lookup[floor][type_bit]);
    }
}
