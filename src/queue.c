#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"


void Queue_init(Queue* queue){
    queue->head = NULL;
    queue->tail = NULL;
}

bool isEmpty(Queue* queue){
    return (queue->head == NULL) && (queue->tail == NULL) ? true : false;
}

QueueNode* peek(Queue* queue){
    return queue->head;
}

QueueNode* enqueue(Queue* queue, int data){
    QueueNode* newQueueNode = malloc(sizeof(QueueNode));
    if (newQueueNode == NULL){
        perror("Could not asllocate memory for new queue node");
        return NULL;
    }
    newQueueNode->data = data;
    newQueueNode->next = NULL;
    if (queue->tail == NULL){
        queue->tail = newQueueNode;
        queue->head = newQueueNode;
    }else{
        queue->tail->next = newQueueNode;
        queue->tail = newQueueNode;
    }
    return newQueueNode;
}

int dequeue(Queue* queue){
    if (queue->head == NULL){
        return -1;//empty
    }

    QueueNode* temp = queue->head;
    int tempData = queue->head->data;
    if (queue->head->next == NULL){
        free(queue->head);
        queue->head = NULL;
        queue->tail = NULL;
    }else{
        queue->head = queue->head->next;
        free(temp);
    }
    return tempData;
}

void clearQueue(Queue* queue){
    while (queue->tail != NULL){
        dequeue(queue);
    }
}

void printQueue(Queue* q){
    QueueNode* curr = q->head;

    printf("\n");
    while (curr != NULL){
        printf("%d->", curr->data);
        curr = curr->next;
    }
}
