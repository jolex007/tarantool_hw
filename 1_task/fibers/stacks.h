#ifndef _STACKS_H_
#define _STACKS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/mman.h>

#define stack_size 1024 * 1024

static void *
allocate_stack() {
	void *stack = malloc(stack_size);
	mprotect(stack, stack_size, PROT_READ | PROT_WRITE | PROT_EXEC);
	return stack;
}

static void
deallocate_stack(void* stack) {
    free(stack);
}

#endif // _STACKS_H_