#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>

#define PUZZLE_QUESTIONS (const char*[]) {"What is 1+1"}
#define PUZZEL_ANSWERS (const char*[]) {"2"}

// Update this count every time a new event is added to the Events
#define TOTAL_EVENTS_COUNT 10 // update this count every time a new event is added to the Events
typedef enum Event{
    NORMAL,
    BLOCKED, //Not sure about this (you should not be able to enter a blocked room unless you have a pickaxe?)
    LOCKED, // Need a key to open it 
    FIRE_TRAP, // -25 health
    POISON_TRAP, // -15 health
    PIT_TRAP, // -100 health if no ladder to climb out
    PUZZLE, // Array of puzzeles and answers
    NPC_BOSS, // -50 health if no sword or shield
    NPC_TRADE, // trades 2 items for any item of choice. (LIke trade 2 items for a key, or ladder);
    NPC_TALK, // Just say random gibberish from a an array of random facts
} Event;

typedef struct EventNode{
    Event data;
    struct EventNode* next;
} EventNode;

EventNode* EventNode_construct(Event event);
EventNode* EventList_insert(EventNode** head, Event event);
void EventList_delete(EventNode** head, Event event);
int eventListCount(EventNode* head);
void freeEventNode(EventNode* eventNode);
void freeEventList(EventNode** head);
void eventListToArray(EventNode* head, int* arr, int arrSize);
void printEventList(EventNode* head);

#endif