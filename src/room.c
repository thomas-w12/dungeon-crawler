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
    strcpy(room->name, name);
    strcpy(room->description, description);
    room->north = north;
    room->south = south;
    room->west = west;
    room->east = east;
    
    room->events = events;
    room->items = items;

    return room;
}

Room* constructRandomRoom(int roomCount){
    // for every randomly generated room, randomly pick a number from 0 to max items in room, 
    // whatever no 'n' is picked, randomly get n numbers from 0 to maxitemscount that represents the item index;
    // if there are 3 or more items in a room, add a LOCKED event to the room;

    ItemNode* items = NULL;
    EventNode* events = NULL;
    Room* room = Room_construct(roomCount, "Test", "Test room", NULL, NULL, NULL, NULL, events, items);

    return room;
}

void generateLayout(Room*** roomsPtr, int* roomCount, int noRoomsToAdd, int* allocRoomsSize){
    Room* firstRoom = constructRandomRoom(*roomCount);
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
        printf("\nReallocating: %d %d", *allocRoomsSize, expectedSize);
    }
}

void expandRoom(Room*** roomsPtr, Room* firstRoom, int* roomCount, int noRoomsToAdd, int* allocRoomsSize){
    reallocRooms(roomsPtr, allocRoomsSize, (*roomCount + noRoomsToAdd)); // only reallocate if needed

    Room** rooms = (*roomsPtr);

    Queue roomQueue; //maybe change to roomLevelQueue;
    Queue_init(&roomQueue);

    enqueue(&roomQueue, firstRoom->ID);

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

        generateRandomIntArr(directions, 0, MAX_DIRECTIONS-1, noOfConnections, filledCount);

        printf("\nRoom ID: %d, Connections: %d, Filled: %d", room->ID, noOfConnections, filledCount);
        for (int i=0;i<MAX_DIRECTIONS;i++){
            printf("\ndirections[%d]: %d", i, directions[i]);
        }

        // Basically a new room has at most filledCount(probably 1) connections already
        for (int i=filledCount; i<(noOfConnections-filledCount); i++){
            if (addedRoomsCount >= noRoomsToAdd) break;

            int direction = directions[i];
            Room* newRoom = constructRandomRoom(*roomCount);
            
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
        printQueue(&roomQueue);
    }
    clearQueue(&roomQueue);
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


// Room* parseRoom(char* line, Room* rooms[]){
//     int ID;
//     char name[10]; //Change to a global like MAX_NAME_LEN
//     char description[20];
//     Room* north;
//     Room* south;
//     Room* west;
//     Room* east;
//     // RoomEventNode events;
//     Item* items[MAX_ITEMS_IN_ROOM];
//     int itemCount = 0;

//     int* connections = (int*)malloc(sizeof(int)*4); // Four possible connection N S W E
//     if (connections == NULL) {
//         printf("\nCould not create room connections");
//         return NULL;
//     }

//     char* token = strtok(line, ",");

//     int index = 0;
//     while (token != NULL){
//         switch(index){
//             case 0:
//                 ID = strtol(token, NULL, 10);
//                 break;
//             case 1:
//                 strcpy(name, token);
//                 break;
//             case 2:
//                 strcpy(description, token);
//                 break;
//             case 3:
//                 if (strcmp(token, "NULL") != 0){
//                     north = rooms[strtol(token, NULL, 10)];
//                 }else{
//                     north = NULL;
//                 }
//                 break;
//             case 4:
//                 if (strcmp(token, "NULL") != 0){
//                     south = rooms[strtol(token, NULL, 10)];
//                 }else{
//                     south = NULL;
//                 }
//                 break;
//             case 5:
//                 if (strcmp(token, "NULL") != 0){
//                     west = rooms[strtol(token, NULL, 10)];
//                 }else{
//                     west = NULL;
//                 }
//                 break;
//             case 6:
//                 if (strcmp(token, "NULL") != 0){
//                     east = rooms[strtol(token, NULL, 10)];
//                 }else{
//                     east = NULL;
//                 }
//                 break;
//             case 7:
//             case 8:
//             case 9: // There are max 3 items in the room
//                 items[itemCount] = Item_construct(strtol(token, NULL, 10));
//                 itemCount++;
//                 break;
//         }
//         token = strtok(NULL, ",");
//         index ++;
//     }
    
//     if (index < 7) return NULL; // Index must be greater than (room with 1 or more items) or equal to 7 (room with zero items) for all valid room line [Count the number of commas + 1 in the layout that is the index]

//     return Room_construct(ID, name, description, north, south, west, east, items, itemCount);
// }

// int loadLayout(char* layoutStateFPath, Room* rooms[], int* roomCount){
//     FILE* fp = fopen(layoutStateFPath, "r");

//     if (fp == NULL){
//         perror("Error openning layout file");
//         return EXIT_FAILURE;
//     }

//     // Read the number of rooms from the file (first line)
//     fscanf(fp, "%d", roomCount);
//     // printf("\nRoom count: %d", *roomCount);

//     // allocate memory for roomCount rooms
//     for (int i=0; i<*roomCount;i++){
//         Room* room = (Room*)malloc(sizeof(Room));
//         if (room == NULL){
//             printf("\nCould not create room");
//             rooms[i] = NULL; // Not sure about this part (It is supposed to fill every space of failed allocation with null)
//             continue;
//         }
//         rooms[i] = room;
//     }

//     int eof = 0;
//     int index = 0;
//     while (eof != EOF){
//         char line[MAX_ROOM_LINE_LEN];
//         if (fgets(line, MAX_ROOM_LINE_LEN, fp) != NULL){
//             // printf("\n%s", line);
//             Room* room = parseRoom(line, rooms);
//             if (room != NULL){
//                 rooms[index] = room;
//                 index ++;
//             }
//         }else{
//             eof = EOF;
//         }
//     }

//     fclose(fp);
//     return EXIT_SUCCESS;
// }

// void serializeRoom(Room* room, char* line){
//     // Or just do fprintf(f, "%d", room->ID);
//     // 12 is the Maximum character length for an integer 2147483647
//     char roomIDStr[12];
//     sprintf(roomIDStr, "%d", room->ID);
//     strcat(line, roomIDStr);
//     strcat(line, ",");

//     strcat(line, room->name);
//     strcat(line, ",");
//     strcat(line, room->description);
//     strcat(line, ",");

//     if (room->north != NULL){
//         char northIDStr[12];
//         sprintf(northIDStr, "%d", room->north->ID);
//         strcat(line, northIDStr);
//     }else{
//         strcat(line, "NULL");
//     }
//     strcat(line, ",");

//     if (room->south != NULL){
//         char southIDStr[12];
//         sprintf(southIDStr, "%d", room->south->ID);
//         strcat(line, southIDStr);
//     }else{
//         strcat(line, "NULL");
//     }
//     strcat(line, ",");

//     if (room->west != NULL){
//         char westIDStr[12];
//         sprintf(westIDStr, "%d", room->west->ID);
//         strcat(line, westIDStr);
//     }else{
//         strcat(line, "NULL");
//     }
//     strcat(line, ",");
    
//     if (room->east != NULL){
//         char eastIDStr[12];
//         sprintf(eastIDStr, "%d", room->east->ID);
//         strcat(line, eastIDStr);
//     }else{
//         strcat(line, "NULL");
//     }

//     for (int i=0;i<room->itemsCount;i++){
//         strcat(line, ",");
//         char itemIDStr[12];
//         sprintf(itemIDStr, "%d", room->items[i]->ID);
//         strcat(line, itemIDStr);
//     }

//     strcat(line, "\n");
//     // printf("\n%s", line);
// }

// int saveLayout(char* layoutStateFPath, Room* rooms[], int roomCount){
//     FILE* f = fopen(layoutStateFPath, "w");

//     if (f == NULL){
//         perror("Error openning layout file");
//         return EXIT_FAILURE;
//     }
//     // The first line is the number of rooms;
//     fprintf(f, "%d\n", roomCount);

//     for (int i=0; i<roomCount; i++){
//         char line[MAX_ROOM_LINE_LEN] = "";
//         serializeRoom(rooms[i], line);
//         // printf("\n%s", line);
//         fprintf(f, "%s", line);
//     }

//     // fseek(f, 0, SEEK_SET);  // (Ignore) Move to beginning after every write before reading (because file is opened in w+ mode)
//     fclose(f);
//     printf("\nSaved layout");
//     return EXIT_SUCCESS;
// }
