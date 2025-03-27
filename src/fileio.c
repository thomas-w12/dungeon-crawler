#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        fprintf(file, "%d,%s,%s,", room->ID, room->name, room->description);

        fprintf(file, "%d,%d,%d,%d,", 
                (room->north ? room->north->ID : DNE),
                (room->south ? room->south->ID : DNE),
                (room->west ? room->west->ID : DNE),
                (room->east ? room->east->ID : DNE));

        int arr[MAX_ROOM_EVENTS];
        eventListToArray(room->events, arr, MAX_ROOM_EVENTS);
        for (int j = 0; j < MAX_ROOM_EVENTS; j++) {
            fprintf(file, "%d,", arr[j]);
        }
        
        for (int j = 0; j < room->itemsCount; j++) {
            fprintf(file, "%d,", room->items[j]->ID);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int loadLayout(const char* layoutStateFPath, Room** rooms, int* roomCount) {
    FILE* file = fopen(layoutStateFPath, "r");

    if (file == NULL) {
        perror("Error opening layout file");
        return EXIT_FAILURE;
    }

    fscanf(file, "%d", roomCount);

    for (int i = 0; i < *roomCount; i++) {
        rooms[i] = (Room*)malloc(sizeof(Room));
        if (rooms[i] == NULL) {
            printf("Memory allocation failed for room %d\n", i);
            continue;
        }

        int id, northID, southID, westID, eastID;
        char name[10], description[30];

        fscanf(file, "%d,%10[^,],%30[^,],%d,%d,%d,%d,", 
               &id, name, description, &northID, &southID, &westID, &eastID); //30 here reads at most 30 characters as the description and 10 as the name

        rooms[i]->ID = id;
        strcpy(rooms[i]->name, name);
        strcpy(rooms[i]->description, description);
        rooms[i]->north = (northID != DNE) ? rooms[northID] : NULL;
        rooms[i]->south = (southID != DNE) ? rooms[southID] : NULL;
        rooms[i]->west = (westID != DNE) ? rooms[westID] : NULL;
        rooms[i]->east = (eastID != DNE) ? rooms[eastID] : NULL;
        rooms[i]->itemsCount = 0;

        rooms[i]->events = NULL;
        for (int j=0; j<MAX_ROOM_EVENTS; j++){
            int event;
            fscanf(file, "%d,", &event);
            if (event != DNE){
                rooms[i]->events = EventList_insert(rooms[i]->events, event);
            }
        }

        while (fgetc(file) != '\n' && !feof(file)) {
            fseek(file, -1, SEEK_CUR); // Go back one char from current position(fgetc pushed it forward)
            int itemID;
            fscanf(file, "%d,", &itemID);
            rooms[i]->items[rooms[i]->itemsCount] = Item_construct(itemID);
            rooms[i]->itemsCount++;
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int savePlayerState(const char* playerStateFPath, Player* player) {
    FILE* file = fopen(playerStateFPath, "w");

    if (file == NULL) {
        perror("Error opening player state file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s,%d,%d,%d,", player->name, player->currentRoom, player->health, player->score);
    for (int i = 0; i < MAX_PLAYER_ITEMS; i++) {
        if (player->inventory[i] != NULL) {
            fprintf(file, "%d,", player->inventory[i]->ID);
        }
    }

    fprintf(file, "\n");
    fclose(file);
    return EXIT_SUCCESS;
}

int loadPlayerState(const char* playerStateFPath, Player* player) {
    FILE* file = fopen(playerStateFPath, "r");

    if (file == NULL) {
        perror("Error opening player state file");
        return EXIT_FAILURE;
    }

    fscanf(file, "%9[^,],%d,%d,%d,", player->name, &player->currentRoom, &player->health, &player->score);
    player->itemsCount = 0;

    while (fgetc(file) != '\n' && !feof(file)) {
        int itemID;
        fscanf(file, "%d,", &itemID);
        player->inventory[player->itemsCount++] = Item_construct(itemID);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
