#include "fiber.h"
#include "../queue/scheduler.h"


static __thread Fiber* current_fiber;

void
SetupFiber(Fiber* fiber, void (*routine)(), Scheduler* scheduler) {
    fiber->stack_ = allocate_stack();
    StackView stack_view;
    SetupStackView(&stack_view, fiber->stack_, stack_size);
    MakeCoroutine(&fiber->coroutine_, &stack_view, routine);

    fiber->scheduler_ = scheduler;
}

void
DeleteFiber(Fiber* fiber) {
    deallocate_stack(fiber->stack_);
    free(fiber);
}

void
RunFiber(Fiber* fiber) {
    current_fiber = fiber;
    Resume(&fiber->coroutine_);
    current_fiber = NULL;

    if (IsCompleted(&fiber->coroutine_)) {
        DeleteFiber(fiber);
    } else {
        SubmitTask(fiber->scheduler_, fiber);
    }
}

void
SpawnFiber(void (*routine)(), Scheduler* scheduler) {
    Fiber* fiber = malloc(sizeof(Fiber));
    SetupFiber(fiber, routine, scheduler);

    SubmitTask(scheduler, fiber);
}



void
Yield() {
    Suspend();
}