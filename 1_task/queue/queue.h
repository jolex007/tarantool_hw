#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

typedef struct Node_str Node;

typedef struct
Queue_str {
    Node* head_;
    bool closed_;
} Queue;

void
SetupQueue(Queue* queue);

void
QueuePush(Queue* queue, void* val);

void*
QueuePop(Queue* queue);

void
CloseQueue(Queue* queue);

void
CancelQueue(Queue* queue);

#endif // _QUEUE_H_