/**
 * @file
 * @brief Elevator objekt
 */
#include <stdbool.h>


typedef enum State { 
    STANDBY, 
    DOORS_OPEN, 
    GOING_UP, 
    GOING_DOWN, 
    EMERGENCY
} State;


typedef struct Elevator {
    State state;
    int current_floor;
    bool floor_sensor_triggered;
    bool emergency_stop;
    bool door_open;
    bool last_direction;
}  Elevator;
