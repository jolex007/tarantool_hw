#include "scheduler.h"
#include <stdio.h>
#include "../fibers/fiber.h"

void
SetupScheduler(Scheduler* scheduler) {
    SetupQueue(&scheduler->queue_);
}

void
SubmitTask(Scheduler* scheduler, Fiber* fiber) {
    QueuePush(&scheduler->queue_, fiber);
}

void
RunScheduler(Scheduler* scheduler) {
    Fiber* fiber = NULL;

    while ((fiber = QueuePop(&scheduler->queue_)) != NULL) {
        RunFiber(fiber);
    }
}