#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct QueueNode{
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue{
    QueueNode* head;
    QueueNode* tail;
} Queue;

void Queue_init(Queue* queue);
bool isEmpty(Queue* queue);
QueueNode* peek(Queue* queue);
QueueNode* enqueue(Queue* queue, int data);
int dequeue(Queue* queue);
void printQueue(Queue* q);
void clearQueue(Queue* queue);

#endif