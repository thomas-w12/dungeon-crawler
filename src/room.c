#include <stdlib.h>
#include <time.h>
#include "../include/room.h"
#include "../include/queue.h"
#include "../include/global.h"

void Room_destroy(Room* room){
    if (room == NULL){
        return;
    }
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
    
    freeEventList(&room->events);
    freeItemList(&room->items);
    free(room);
}

Room* Room_construct(int ID, Room* north, Room* south, Room* west, Room* east, EventNode* events, ItemNode* items){
    Room* room = malloc(sizeof(Room));
    if (room == NULL){
        printf("Could not create room\n");
        return NULL;
    }

    room->ID = ID;
    room->north = north;
    room->south = south;
    room->west = west;
    room->east = east;
    
    room->events = events;
    room->items = items;

    return room;
}

Room* constructRandomRoom(int roomCount, int noItems, int noEvents){
    ItemNode* items = NULL;
    int* itemsArr = malloc(noItems*sizeof(int));
    generateRandomIntArr(itemsArr, noItems, 0, TOTAL_ITEMS_COUNT-1, 0);
    for (int i=0; i<noItems; i++){
        int itemID = itemsArr[i];
        ItemList_insert(&items, Item_construct(itemID));
    }

    EventNode* events = NULL;
    int* eventsArr = malloc(noEvents*sizeof(int));
    generateRandomIntArr(eventsArr, noEvents, 0, TOTAL_EVENTS_COUNT-1, 0);
    for (int i=0; i<noEvents; i++){
        int eventNum = eventsArr[i];
        EventList_insert(&events, eventNum);
    }
    
    Room* room = Room_construct(roomCount, NULL, NULL, NULL, NULL, events, items);

    free(eventsArr);
    free(itemsArr);
    return room;
}

void generateLayout(Room*** roomsPtr, int* roomCount, int noRoomsToAdd, int* allocRoomsSize){
    Room* firstRoom = constructRandomRoom(*roomCount, 0, 0);
    if (firstRoom == NULL){
        perror("Could not create room\n");
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
            perror("Could not reallocate memory for rooms\n");
            return;
        }
        *roomsPtr = newPtr;
        (*allocRoomsSize) = (expectedSize+20);
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
    if (generateRandomIntArrProb(roomsItemsCountArr, noRoomsToAdd, 0, MAX_ITEMS_IN_ROOM, itemsOccurenceProbArr, (MAX_ITEMS_IN_ROOM+1)) == NULL){
        printf("There was an issue generating the random probability array.\n");
        return;
    }

     // Array that stores a random number of events for all rooms to add
    int* roomsEventsCountArr = malloc(sizeof(int)*noRoomsToAdd);
    int eventsOccurenceProbArr[] = {45, 40, 10, 5}; // {0: 45%, 1: 40%, 2: 10%, 3: 5%}
    if (generateRandomIntArrProb(roomsEventsCountArr, noRoomsToAdd, 0, MAX_ROOM_EVENTS, eventsOccurenceProbArr, (MAX_ROOM_EVENTS+1)) == NULL){
        printf("There was an issue generating the random probability array.\n");
        return;
    }

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
                perror("Could not create room\n");
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
    }
    clearQueue(&roomQueue);
    free(roomsItemsCountArr);
    free(roomsEventsCountArr);
}

void displayRoom(Room* room){
    if (room == NULL){
        printf("Room does not exist\n");
        return;
    }
    printf("Room - ID: %d\n", room->ID);
    printf("Items in room (%d): \n", itemListCount(room->items));
    printItemList(room->items);
}

void displayRooms(Room** rooms, int roomCount){
    if (roomCount == 0){
        printf("There are no rooms!\n");
        return;
    }

    for (int i = 0; i<roomCount; i++){
        displayRoom(rooms[i]);
    }
}

void freeRooms(Room*** roomsPtr, int* roomCount){
    Room** rooms = *roomsPtr;
    if ((*roomCount == 0) && (rooms == NULL)){
        printf("There are no rooms to free!\n");
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

