#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "command_parser.h"
#include "event.h"
#include "queue.h"

#define MAX_ROOMS 10
#define MAX_ROOM_LINE_LEN 100 // Max length of the room line stored in the layout.txt
#define MAX_ITEMS_IN_ROOM 3
#define MAX_ROOM_EVENTS 3
#define MAX_DIRECTIONS 4
#define PROB_ITEM_IN_ROOM 0.2 // Probability of having an item in a room
#define PROB_EVENT_IN_ROOM 0.1 // Probability of having an event in a room
#define EXPAND_ROOM_COUNT 20

typedef enum DirectionsIndex{
    NorthIndex,
    SouthIndex,
    WestIndex,
    EastIndex
} DirectionsIndex;

typedef struct Room{
    int ID; 
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    EventNode* events; //points to the first event which holds the rest of list
    ItemNode* items;
} Room;

void Room_destroy(Room* room);
Room* Room_construct(int ID, Room* north, Room* south, Room* west, Room* east, EventNode* events, ItemNode* items);
void reallocRooms(Room*** roomsPtr, int* allocRoomsSize, int expectedSize);
void expandRoom(Room*** roomsPtr, Room* firstRoom, int* roomCount, int noRoomsToAdd, int* allocRoomsSize);
void generateLayout(Room*** roomsPtr, int* roomCount, int noRoomsToAdd, int* allocRoomsSize);
void displayRoom(Room* room);
void displayRooms(Room** rooms, int roomCount);
void freeRooms(Room*** roomsPtr, int* roomCount);

#endif