#include "coroutine_impl.h"
#include <stdio.h>

static __thread Coroutine* current_coroutine = NULL;

void
Suspend() {
    if (!current_coroutine) {
        perror("Suspended not in coroutine");
    }
    SwitchTo(&current_coroutine->context_, &current_coroutine->caller_context_);
}

void
TerminateCoroutine(Coroutine* coro) {
    coro->is_finished_ = true;
    Suspend();
}

static void
Trampoline(void (*routine)()) {

    current_coroutine->routine_();

    TerminateCoroutine(current_coroutine);
}


void
MakeCoroutine(Coroutine* coro, StackView* stack, void (*routine)()) {
    coro->is_finished_ = false;
    coro->routine_ = routine;

    SetupMachineContext(&coro->context_, stack, Trampoline);
}

void
Resume(Coroutine* coro) {
    Coroutine* caller = current_coroutine;
    current_coroutine = coro;

    SwitchTo(&coro->caller_context_, &coro->context_);

    current_coroutine = caller;
}

bool
IsCompleted(Coroutine* coro) {
    return coro->is_finished_;
}

