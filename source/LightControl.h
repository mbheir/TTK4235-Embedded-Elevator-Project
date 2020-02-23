
#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H
#include <stdbool.h>
#include "hardware.h"
#include "queue.h"

void lightUpdateFromQueue(Queue queue);

#endif
