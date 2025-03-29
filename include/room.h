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

typedef enum DirectionsIndex{
    NorthIndex,
    SouthIndex,
    WestIndex,
    EastIndex
} DirectionsIndex;

typedef struct Room{
    int ID; 
    char name[10];
    char description[30];
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    EventNode* events; //points to the first event which holds the rest of list
    ItemNode* items;
    // int itemsCount;
} Room;

void Room_destroy(Room* room);
Room* Room_construct(int ID, char* name, char* description, Room* north, Room* south, Room* west, Room* east, EventNode* events, ItemNode* items);
// Room* addRoom(char* name, char* description);
// Room* parseRoom(char* line, Room* rooms[]);
// void serializeRoom(Room* room, char* line);
void reallocRooms(Room*** roomsPtr, int* allocRoomsSize, int expectedSize);
void expandRoom(Room*** roomsPtr, Room* firstRoom, int* roomCount, int noRoomsToAdd, int* allocRoomsSize);
void generateLayout(Room*** roomsPtr, int* roomCount, int noRoomsToAdd, int* allocRoomsSize);
// int saveLayout(const char* layoutStateFPath, Room** rooms, int roomCount);
// int loadLayout(const char* layoutStateFPath, Room** rooms, int* roomCount);
void displayRoom(Room* room);
void displayRooms(Room** rooms, int roomCount);
void freeRooms(Room*** roomsPtr, int* roomCount);

#endif