#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct
Node_str {
    void* val;
    struct Node_str *next;
} Node;

void
Enqueue(Node** head_, void* val) {
    Node *new_Node = malloc(sizeof(Node));
    if (!new_Node) return;

    new_Node->val = val;
    new_Node->next = *head_;

    *head_ = new_Node;
}

void*
Dequeue(Node** head_) {
    Node* current;
    Node* prev = NULL;
    void* retval = NULL;

    if (*head_ == NULL) return NULL;

    current = *head_;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    retval = current->val;
    free(current);
    
    if (prev)
        prev->next = NULL;
    else
        *head_ = NULL;

    return retval;
}

void
CloseQueueImpl(Queue* queue, bool clear) {
    queue->closed_ = true;
    if (clear) {
        while (Dequeue(&queue->head_) != NULL) {
            // Poped one element
        }
    }
}

void
SetupQueue(Queue* queue) {
    queue->head_ = NULL;
    queue->closed_ = false;
}

void
QueuePush(Queue* queue, void* val) {
    Enqueue(&queue->head_, val);
}

void*
QueuePop(Queue* queue) {
    return Dequeue(&queue->head_);
}

void
CloseQueue(Queue* queue) {
    CloseQueueImpl(queue, false);
}

void
CancelQueue(Queue* queue) {
    CloseQueueImpl(queue, true);
}

