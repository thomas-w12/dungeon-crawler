#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>

#define PUZZLE_QUESTIONS (const char*[]) {"I have hands but cannot clap. What am I?", "What comes once in a minute, twice in a moment, but never in a thousand years?", "I have a tail and a head, but no body. What am I?", "Which planet is known as the Red Planet?", "What has keys but can't open locks?", "What number comes next in the sequence? 2, 4, 8, 16, __?", "What is the square root of 144?", "What metal is primarily used to make wires?", "What does malloc return if memory allocation was unsuccessfull?"}
#define PUZZLE_ANSWERS (const char*[]) {"clock", "m", "coin", "mars", "keyboard", "32", "12", "copper", "null"}
#define PUZZLE_COUNT 9

// Update this count every time a new event is added to the Events
#define TOTAL_EVENTS_COUNT 10
typedef enum Event{
    NORMAL,
    BLOCKED, // You need a pickaxe to break and enter
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