#ifndef _MACHINE_CONTEXT_H_
#define _MACHINE_CONTEXT_H_

#include <inttypes.h>
#include <stdlib.h>

typedef struct StackView_str {
    void* begin_;
    size_t size_;
} StackView;

void SetupStackView(StackView* view, void* stack_ptr, size_t size);

typedef struct MachineContext_str {
  void* rsp_;
} MachineContext;

void SetupMachineContext(MachineContext* cntx, StackView* stack, void (*Trampoline)());
void SwitchTo(MachineContext* from, MachineContext* to);

#endif // machine_context.h