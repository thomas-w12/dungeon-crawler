#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fileio.h"

int saveLayout(const char* layoutStateFPath, Room* rooms[], int roomCount) {
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
                (room->north ? room->north->ID : -1),
                (room->south ? room->south->ID : -1),
                (room->west ? room->west->ID : -1),
                (room->east ? room->east->ID : -1));

        for (int j = 0; j < room->itemsCount; j++) {
            fprintf(file, "%d,", room->items[j].ID);
        }

        fprintf(file, "\n");
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int loadLayout(const char* layoutStateFPath, Room* rooms[], int* roomCount) {
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
        char name[10], description[20];

        fscanf(file, "%d,%9[^,],%19[^,],%d,%d,%d,%d,", 
               &id, name, description, &northID, &southID, &westID, &eastID);

        rooms[i]->ID = id;
        strcpy(rooms[i]->name, name);
        strcpy(rooms[i]->description, description);
        rooms[i]->north = (northID != -1) ? rooms[northID] : NULL;
        rooms[i]->south = (southID != -1) ? rooms[southID] : NULL;
        rooms[i]->west = (westID != -1) ? rooms[westID] : NULL;
        rooms[i]->east = (eastID != -1) ? rooms[eastID] : NULL;
        rooms[i]->itemsCount = 0;

        while (fgetc(file) != '\n' && !feof(file)) {
            int itemID;
            fscanf(file, "%d,", &itemID);
            rooms[i]->items[rooms[i]->itemsCount++] = Item_construct(itemID);
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

    fprintf(file, "%s,%d,", player->name, player->currentRoom);
    for (int i = 0; i < player->itemsCount; i++) {
        fprintf(file, "%d,", player->items[i].ID);
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

    fscanf(file, "%9[^,],%d,", player->name, &player->currentRoom);
    player->itemsCount = 0;

    while (fgetc(file) != '\n' && !feof(file)) {
        int itemID;
        fscanf(file, "%d,", &itemID);
        player->items[player->itemsCount++] = Item_construct(itemID);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
