#include <stdio.h>
#include <stdlib.h>

#include "../include/global.h"
#include "../include/event.h"


EventNode* EventNode_construct(Event event){
    EventNode* eventNode = malloc(sizeof(EventNode));
    if (eventNode == NULL){
        perror("Could not allocate memory for eventnode");
        return NULL;
    }

    eventNode->data = event;
    eventNode->next = NULL;

    return eventNode;
}

EventNode* EventList_insert(EventNode** head, Event event){
    EventNode* eventNode = EventNode_construct(event);
    if (eventNode == NULL){
        perror("Failed Event List insert");
        return NULL;
    }
    // cannot have duplicate events
    if (*head == NULL){
        *head = eventNode;
    }else{
        EventNode* curr = *head;

        while(curr->next != NULL){
            if (curr->data == event){
                perror("Duplicate events are not allowed");
                return NULL;
            }
            curr = curr->next;
        }

        curr->next = eventNode;
    }

    return eventNode;
}

void EventList_delete(EventNode** head, Event event){
    if (*head == NULL){
        return;
    }else if ((*head)->data == event){
        if ((*head)->next == NULL){
            free(head);
            head = NULL;
            return;
        }
        EventNode* temp = (*head)->next;
        free(*head);
        *head = temp;
    }else{
        EventNode* prev = *head;
        EventNode* curr = (*head)->next;

        while((curr != NULL) && (curr->data != event)){
            prev = curr;
            curr = curr->next;
        }

        if (curr != NULL){
            prev->next = curr->next;
            free(curr);
        }
    }
}

int eventListCount(EventNode* head){
    EventNode* curr = head;
    int count = 0;
    while (curr != NULL){
        curr = curr->next;
        count++;
    }
    return count;
}

void eventListToArray(EventNode* head, int* arr, int arrSize){
    EventNode* curr = head;
    for (int i=0; i<arrSize; i++){
        if (curr == NULL){
            arr[i] = DNE;
        }else{
            arr[i] = curr->data;
            curr = curr->next;
        }
    }
}

void freeEventNode(EventNode* eventNode){
    if (eventNode == NULL){
        return;
    }
    freeEventNode(eventNode->next);
    free(eventNode);
}

void freeEventList(EventNode* head){
    freeEventNode(head);
    head = NULL;
}

void printEventList(EventNode* head){
    printf("\n");
    EventNode* curr = head;
    while (curr != NULL){
        printf("%d->", curr->data);
        curr = curr->next;
    }
}