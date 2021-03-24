#ifndef _FIBER_H_
#define _FIBER_H_

#include "stacks.h"
#include "../coroutine/coroutine_impl.h"

typedef struct Scheduler_str Scheduler;

typedef struct
Fiber_str {
    Scheduler* scheduler_;
    void* stack_;
    Coroutine coroutine_;
} Fiber;

void
SetupFiber(Fiber* fiber, void (*routine)(), Scheduler* scheduler);

void
RunFiber(Fiber* fiber);

void
SpawnFiber(void (*routine)(), Scheduler* scheduler);


#endif