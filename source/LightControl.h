
#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H
#include <stdbool.h>
#include "hardware.h"

void lightUpdateFromQueue(bool up_queue[], bool down_queue[], bool inside_queue[]);


#endif
