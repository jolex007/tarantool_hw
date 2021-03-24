#include "machine_context.h"

typedef struct StackSavedMachineContext_str {
  // Callee-saved registers
  // Saved manually in SwitchMachineContext
  void* rbp;
  void* rbx;

  void* r12;
  void* r13;
  void* r14;
  void* r15;

  // Saved automatically by 'call' instruction
  void* rip;
} StackSavedMachineContext;

extern void SwitchMachineContext(void* from_rsp, void* to_rsp);

void SetupStackView(StackView* view, void* stack_ptr, size_t size) {
    view->begin_ = stack_ptr;
    view->size_ = size;
}

void SetupMachineContext(MachineContext* cntx, StackView* view, void (*Trampoline)()) {
    char* stack_ptr = view->begin_ + view->size_;

    // Allign ptr
    size_t shift_for_align = (size_t)(view->begin_ - sizeof(unsigned long int)) % 16;
    stack_ptr -= shift_for_align;

    stack_ptr -= sizeof(StackSavedMachineContext);

    StackSavedMachineContext* stack_saved_context = (StackSavedMachineContext*)stack_ptr;
    stack_saved_context->rip = (void*)Trampoline;

    cntx->rsp_ = stack_saved_context;
}


void SwitchTo(MachineContext* from, MachineContext* to) {
    SwitchMachineContext(&from->rsp_, &to->rsp_);
}


