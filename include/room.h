#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "command_parser.h"

#define MAX_ROOMS 10
#define MAX_ROOM_LINE_LEN 100 // Max length of the room line stored in the layout.txt
#define MAX_ITEMS_IN_ROOM 3
#define DNE -1 // (Ignore for now) Does not exist. Used to represent an int array element that does not exist (since NULL can't be used).

typedef struct Room{
    int ID; 
    char name[10];
    char description[30];
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    Item* items[MAX_ITEMS_IN_ROOM];
    int itemsCount;
} Room;

void Room_destroy(Room* room);
Room* Room_construct(int ID, char* name, char* description, Room* north, Room* south, Room* west, Room* east, Item* items[], int itemCount);
// Room* addRoom(char* name, char* description);
Room* parseRoom(char* line, Room* rooms[]);
void serializeRoom(Room* room, char* line);
void generateLayout(Room* rooms[], int* roomCount);
int saveLayout(const char* layoutStateFPath, Room* rooms[], int roomCount);
int loadLayout(const char* layoutStateFPath, Room* rooms[], int* roomCount);
void displayRoom(Room* room);
void displayRooms(Room* rooms[], int roomCount);
void freeRoomConnections(int** roomConnections, int roomCount);
void freeRooms(Room* rooms[], int* roomCount);

#endif