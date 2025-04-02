#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/global.h"
#include "../include/fileio.h"
#include "../include/event.h"

int saveLayout(const char* layoutStateFPath, Room** rooms, int roomCount) {
    FILE* file = fopen(layoutStateFPath, "w");

    if (file == NULL) {
        perror("Error opening layout file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%d\n", roomCount);

    for (int i = 0; i < roomCount; i++) {
        Room* room = rooms[i];
        fprintf(file, "%d,", room->ID);

        fprintf(file, "%d,%d,%d,%d,", 
                (room->north ? room->north->ID : DNE),
                (room->south ? room->south->ID : DNE),
                (room->west ? room->west->ID : DNE),
                (room->east ? room->east->ID : DNE));
        
        EventNode* currEvent = room->events;
        for (int j=0; j<MAX_ROOM_EVENTS; j++){
            if (currEvent == NULL){
                fprintf(file, "%d,", DNE);
            }else{
                fprintf(file, "%d,", currEvent->data);
                currEvent = currEvent->next;
            }
        }

        ItemNode* currItem = room->items;
        for (int j=0; j<MAX_ITEMS_IN_ROOM; j++){
            if (currItem == NULL){
                fprintf(file, "%d,", DNE);
            }else{
                fprintf(file, "%d,", currItem->data->ID);
                currItem = currItem->next;
            }
        }
        
        fprintf(file, "\n");
    }

    fclose(file);
    return EXIT_SUCCESS;
}

bool loadLayout(const char* layoutStateFPath, Room*** roomsPtr, int* roomCount, int* allocRoomSize) {
    FILE* file = fopen(layoutStateFPath, "r");

    if (file == NULL) {
        perror("Error opening layout file");
        return false;
    }

    fscanf(file, "%d", roomCount);

    if (*roomCount == 0) return false;

    reallocRooms(roomsPtr, allocRoomSize, *roomCount);
    Room** rooms = *roomsPtr;

    // Allocate memory for roomCount rooms
    for (int i=0; i<*roomCount;i++){
        Room* room = malloc(sizeof(Room));
        if (room == NULL){
            printf("\nCould not create room");
            rooms[i] = NULL; // Not sure about this part (It is supposed to fill every space of failed allocation with null)
            continue;
        }
        rooms[i] = room;
    }

    for (int i = 0; i < *roomCount; i++) {
        if (rooms[i] == NULL) {
            printf("Memory allocation failed for room %d\n", i);
            continue;
        }

        int id, northID, southID, westID, eastID;

        int result = fscanf(file, "%d,%d,%d,%d,%d,", 
               &id, &northID, &southID, &westID, &eastID);
        
        if (result != 5) return false;

        rooms[i]->ID = id;
        rooms[i]->north = (northID != DNE) ? rooms[northID] : NULL;
        rooms[i]->south = (southID != DNE) ? rooms[southID] : NULL;
        rooms[i]->west = (westID != DNE) ? rooms[westID] : NULL;
        rooms[i]->east = (eastID != DNE) ? rooms[eastID] : NULL;

        rooms[i]->events = NULL;
        for (int j=0; j<MAX_ROOM_EVENTS; j++){
            int event;
            fscanf(file, "%d,", &event);
            if (event != DNE){
                EventList_insert(&rooms[i]->events, event);
            }
        }

        rooms[i]->items = NULL;
        for (int j=0; j<MAX_ITEMS_IN_ROOM; j++){
            int itemID;
            fscanf(file, "%d,", &itemID);
            if (itemID != DNE){
                ItemList_insert(&rooms[i]->items, Item_construct(itemID));
            }
        }
    }

    fclose(file);
    return true;
}

int savePlayerState(const char* playerStateFPath, Player* player) {
    FILE* file = fopen(playerStateFPath, "w");

    if (file == NULL) {
        perror("Error opening player state file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s,%d,%d,%d,", player->name, player->currentRoom, player->health, player->score);

    ItemNode* currItem = player->inventory;
    for (int i=0; i<MAX_PLAYER_ITEMS; i++){
        if (currItem == NULL){
            fprintf(file, "%d,", DNE);
        }else{
            fprintf(file, "%d,", currItem->data->ID);
            currItem = currItem->next;
        }
    }

    fprintf(file, "\n");
    fclose(file);
    return EXIT_SUCCESS;
}

bool loadPlayerState(const char* playerStateFPath, Player* player) {
    FILE* file = fopen(playerStateFPath, "r");

    if (file == NULL) {
        perror("Error opening player state file");
        return false;
    }

    char nameBuffer[100]; // Temporary buffer for reading the name
    int result = fscanf(file, "%99[^,],%d,%d,%d,", nameBuffer, &player->currentRoom, &player->health, &player->score);
    
    if (result != 4) return false;

    strcpy(player->name, nameBuffer);
    
    if (player->inventory != NULL){
        printf("Inventory stuff\n\n\n\n");
        freeItemList(&player->inventory);
    }
    for (int j=0; j<MAX_ITEMS_IN_ROOM; j++){
        int itemID;
        fscanf(file, "%d,", &itemID);
        if (itemID != DNE){
            ItemList_insert(&player->inventory, Item_construct(itemID));
        }
    }

    fclose(file);
    return true;
}
