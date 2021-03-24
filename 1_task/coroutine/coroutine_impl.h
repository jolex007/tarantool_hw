#ifndef _COROUTINE_IMPL_
#define _COROUTINE_IMPL_

#define _XOPEN_SOURCE /* Mac compatibility. */
#include "context/machine_context.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/mman.h>

typedef
struct Coroutine_str {
    bool is_finished_;
    void (*routine_)();
    MachineContext context_;
    MachineContext caller_context_;
} Coroutine;

void
MakeCoroutine(Coroutine* coro, StackView* stack, void (*routine)());

extern void
Suspend();

void
Resume(Coroutine* coro);

bool
IsCompleted(Coroutine* coro);

#endif // _COROUTINE_IMPL_