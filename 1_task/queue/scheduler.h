#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "queue.h"
#include "../fibers/fiber.h"

typedef struct
Scheduler_str {
    Queue queue_;
} Scheduler;

void
SetupScheduler(Scheduler* scheduler);

void
SubmitTask(Scheduler* scheduler, Fiber* fiber);

void
RunScheduler(Scheduler* scheduler);

#endif // _SCHEDULER_H_