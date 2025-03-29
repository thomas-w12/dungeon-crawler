#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>

#define TOTAL_EVENTS_COUNT 7 // update this count every time a new event is added to the Events

typedef enum Event{
    NORMAL,
    BLOCKED, //Not sure about this (you should not be able to enter a blocked room unless you have a hammer?)
    LOCKED,
    TRAP,
    PIT_TRAP, // -100 health if no ladder to climb out
    PUZZLE,
    NPC_BOSS, // -50 health if no sword or shield
} Event;

typedef struct EventNode{
    Event data;
    struct EventNode* next;
    // int count; only updated for head node (probably isn't efficient)
} EventNode;

EventNode* EventNode_construct(Event event);
EventNode* EventList_insert(EventNode** head, Event event);
void EventList_delete(EventNode** head, Event event);
int eventListCount(EventNode* head);
void freeEventNode(EventNode* eventNode);
void freeEventList(EventNode* head);
void eventListToArray(EventNode* head, int* arr, int arrSize);
void printEventList(EventNode* head);

#endif