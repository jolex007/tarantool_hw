#ifndef _API_H_
#define _API_H_

#include "../queue/scheduler.h"

void
SpawnFiber(void (*routine)(), Scheduler* scheduler);

void
Yield();

#endif // _API_H_