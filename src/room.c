#include <stdlib.h>
#include <time.h>
#include "../include/room.h"
#include "../include/queue.h"
#include "../include/global.h"

void Room_destroy(Room* room){
    // find all its connections and close the space between them [(or maybe set to null)]
    if (room->north != NULL){
        room->north->south = room->south;
    }
    if (room->south != NULL){
        room->south->north = room->north;
    }
    if (room->west != NULL){
        room->west->east = room->east;
    }
    if (room->east != NULL){
        room->east->west = room->west;
    }
    
    free(room->name);
    free(room->description);

    freeEventList(room->events);
    freeItemList(&room->items);
    free(room);
}

void Room_copy(Room* src, Room* dest){

}

Room* Room_construct(int ID, char* name, char* description, Room* north, Room* south, Room* west, Room* east, EventNode* events, ItemNode* items){
    // Thinking of adding Room** rooms and int* roomCount to the signature so anytime a room is constructed, addition to rooms and increasing room count would be done in one function; (or maybe it should be done in addRoom())
    Room* room = malloc(sizeof(Room));
    if (room == NULL){
        printf("\nCould not create room");
        return NULL;
    }

    room->ID = ID;
    room->name = strdup(name);
    if (room->name == NULL){
        printf("\nCould not create room name");
        free(room);
        return NULL;
    }
    room->description = strdup(description);
    if (room->description == NULL){
        printf("\nCould not create room description");
        free(room->name);
        free(room);
        return NULL;
    }
    room->north = north;
    room->south = south;
    room->west = west;
    room->east = east;
    
    room->events = events;
    room->items = items;

    return room;
}

Room* constructRandomRoom(int roomCount, int noItems, int noEvents){
    // for every randomly generated room, randomly pick a number from 0 to max items in room, 
    // whatever no 'n' is picked, randomly get n numbers from 0 to maxitemscount that represents the item index;
    // if there are 3 or more items in a room, add a LOCKED event to the room;

    ItemNode* items = NULL;
    int* itemsArr = malloc(noItems*sizeof(int));
    // Can also use the probability generation here
    generateRandomIntArr(itemsArr, noItems, 0, TOTAL_ITEMS_COUNT-1, 0);  // -1 becuse index starts from 0
    for (int i=0; i<noItems; i++){
        int itemID = itemsArr[i];
        ItemList_insert(&items, Item_construct(itemID));
    }

    EventNode* events = NULL;
    int* eventsArr = malloc(noEvents*sizeof(int));
    generateRandomIntArr(eventsArr, noEvents, 0, TOTAL_ITEMS_COUNT-1, 0);  // -1 becuse index starts from 0
    for (int i=0; i<noEvents; i++){
        int eventNum = eventsArr[i];
        EventList_insert(&events, i);
    }
    
    Room* room = Room_construct(roomCount, "Test", "Test room", NULL, NULL, NULL, NULL, events, items);

    return room;
}

void generateLayout(Room*** roomsPtr, int* roomCount, int noRoomsToAdd, int* allocRoomsSize){
    Room* firstRoom = constructRandomRoom(*roomCount, 0, 0);
    if (firstRoom == NULL){
        perror("Could not create room");
        return;
    }
    *roomsPtr[firstRoom->ID] = firstRoom;
    (*roomCount)++;
    
    expandRoom(roomsPtr, firstRoom, roomCount, noRoomsToAdd-1, allocRoomsSize);
}

void reallocRooms(Room*** roomsPtr, int* allocRoomsSize, int expectedSize){
    if (expectedSize >= *allocRoomsSize){ 
        Room** newPtr = realloc(*roomsPtr, sizeof(Room*) * (expectedSize+20)); //reallocate memory (expected size)
        if (newPtr == NULL){
            perror("Could not reallocate memory for rooms");
            return;
        }
        *roomsPtr = newPtr;
        (*allocRoomsSize) = (expectedSize+20);
        printf("\nReallocating: %d %d\n", *allocRoomsSize, expectedSize);
    }
}

void expandRoom(Room*** roomsPtr, Room* firstRoom, int* roomCount, int noRoomsToAdd, int* allocRoomsSize){
    reallocRooms(roomsPtr, allocRoomsSize, (*roomCount + noRoomsToAdd)); // only reallocate if needed

    Room** rooms = (*roomsPtr);

    Queue roomQueue; //maybe change to roomLevelQueue;
    Queue_init(&roomQueue);
    enqueue(&roomQueue, firstRoom->ID);

     // Array that stores a random number of items for all rooms to add
    int* roomsItemsCountArr = malloc(sizeof(int)*noRoomsToAdd);
    int itemsOccurenceProbArr[] = {40, 30, 20, 10}; // {0: 40%, 1: 30%, 2: 20%, 3: 10%}
    generateRandomIntArrProb(roomsItemsCountArr, noRoomsToAdd, 0, MAX_ITEMS_IN_ROOM, itemsOccurenceProbArr, (MAX_ITEMS_IN_ROOM+1));

     // Array that stores a random number of events for all rooms to add
    int* roomsEventsCountArr = malloc(sizeof(int)*noRoomsToAdd);
    int eventsOccurenceProbArr[] = {45, 40, 10, 5}; // {0: 45%, 1: 40%, 2: 10%, 3: 5%}
    generateRandomIntArrProb(roomsEventsCountArr, noRoomsToAdd, 0, MAX_ROOM_EVENTS, eventsOccurenceProbArr, (MAX_ROOM_EVENTS+1));

    // Iteratively expand using Breath First Search approach;
    int addedRoomsCount = 0;
    while ((isEmpty(&roomQueue) == false) && (addedRoomsCount < noRoomsToAdd)){
        Room* room = rooms[peek(&roomQueue)->data]; //this is fine because it would not enter if queue is empty

        // we want at least 2 connections, 1 for previous connection and at least 1 for next
        int noOfConnections = generateRandomInt(2, MAX_DIRECTIONS); 
        
        int directions[MAX_DIRECTIONS]; // List of connected directions
        for (int i=0;i<MAX_DIRECTIONS;i++){
            directions[i] = DNE;
        }
        // Prefill directions with already existing connections so won't be repeated;
        int filledCount = 0;
        if (room->north != NULL){
            directions[filledCount] = NorthIndex;
            filledCount ++;
        }
        if (room->south != NULL){
            directions[filledCount] = SouthIndex;
            filledCount ++;
        }
        if (room->west != NULL){
            directions[filledCount] = WestIndex;
            filledCount ++;
        }
        if (room->east != NULL){
            directions[filledCount] = EastIndex;
            filledCount ++;
        }
        generateRandomIntArr(directions, MAX_DIRECTIONS, 0, MAX_DIRECTIONS-1, filledCount);

        // Basically a new room has at most filledCount(probably 1) connections already
        for (int i=filledCount; i<noOfConnections; i++){
            if (i > MAX_DIRECTIONS) break;
            if (addedRoomsCount >= noRoomsToAdd) break;

            int direction = directions[i];
            int noOfItems = roomsItemsCountArr[addedRoomsCount];
            int noOfEvents = roomsEventsCountArr[addedRoomsCount];
            Room* newRoom = constructRandomRoom(*roomCount, noOfItems, noOfEvents);
            
            if (newRoom == NULL){
                perror("Could not create room");
                return;
            }
            switch(direction){
                case NorthIndex:
                    room->north = newRoom;
                    newRoom->south = room;
                    enqueue(&roomQueue, newRoom->ID);
                    break;
                case SouthIndex:
                    room->south = newRoom;
                    newRoom->north = room;
                    enqueue(&roomQueue, newRoom->ID);
                    break;
                case WestIndex:
                    room->west = newRoom;
                    newRoom->east = room;
                    enqueue(&roomQueue, newRoom->ID);
                    break;
                case EastIndex:
                    room->east = newRoom;
                    newRoom->west = room;
                    enqueue(&roomQueue, newRoom->ID);
                    break;
            }
            rooms[newRoom->ID] = newRoom;
            (*roomCount) ++;
            addedRoomsCount ++;
        }
        dequeue(&roomQueue);
        // printQueue(&roomQueue);
    }
    clearQueue(&roomQueue);
    free(roomsItemsCountArr);
    free(roomsEventsCountArr);
}

void displayRoom(Room* room){
    if (room == NULL){
        printf("\nRoom does not exist");
        return;
    }
    printf("\nRoom - ID: %d\tName: %s\tDescription: %s", room->ID, room->name, room->description);
    printf("\nItems in room (%d): ", itemListCount(room->items));
    printItemList(room->items);
    printf("\nRoom Connections: %d %d %d %d", room->north != NULL?room->north->ID:DNE, room->south != NULL?room->south->ID:DNE, room->west != NULL?room->west->ID:DNE, room->east != NULL?room->east->ID:DNE);
    printf("\n");
}

void displayRooms(Room** rooms, int roomCount){
    if (roomCount == 0){
        printf("\nThere are no rooms!");
        return;
    }

    for (int i = 0; i<roomCount; i++){
        displayRoom(rooms[i]);
    }
}

void freeRooms(Room*** roomsPtr, int* roomCount){
    Room** rooms = *roomsPtr;
    if ((*roomCount == 0) && (rooms == NULL)){
        printf("\nThere are no rooms to free!");
        return;
    }
    
    for (int i=0; i<(*roomCount); i++){
        if (rooms[i] != NULL){
            Room_destroy(rooms[i]);
        }
    }

    *roomCount = 0;
    free(rooms);
    *roomsPtr = NULL;
}

