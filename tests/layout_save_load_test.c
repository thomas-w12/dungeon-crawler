#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/item.h"
#include "../include/room.h"
#include "../include/player.h"
#include "../include/fileio.h"

int main(int argc, char *argv[]) {
    
    srand(time(0));

    int allocRoomSize = 10; // initial rooms alloc size
    int roomCount = 0;
    Room** rooms = malloc(sizeof(Room*) * allocRoomSize);
    if (rooms == NULL){
        perror("Could not allocate memory for rooms");
        return EXIT_FAILURE;
    }
    
    char layoutStateFPath[] = {"tests/saved_test_games/layout_save_load_test_output.txt"};
    char expectedLayoutStateFPath[] = {"tests/saved_test_games/layout_save_load_test_expected.txt"};

    
    // Create items to be added to the room
    Item* item1 = Item_construct(0);
    Item* item2 = Item_construct(1);
    Item* item3 = Item_construct(2);

    ItemNode* itemsHead = NULL;
    ItemList_insert(&itemsHead, item1);
    ItemList_insert(&itemsHead, item2);
    ItemList_insert(&itemsHead, item3);

    // Create events to be added to the room
    EventNode* events = NULL;
    EventList_insert(&events, FIRE_TRAP);
    EventList_insert(&events, PUZZLE);
    EventList_insert(&events, BLOCKED);
    EventList_insert(&events, LOCKED);


    // Create a room and add it to the rooms array
    Room* room = Room_construct(0, NULL, NULL, NULL, NULL, events, itemsHead);
    if (room != NULL){
        rooms[room->ID] = room;
        roomCount++;
    }
    displayRoom(room);
    // Create another room and add it to the rooms array
    Room* room1 = Room_construct(1, NULL, NULL, NULL, NULL, NULL, NULL);
    if (room1 != NULL){
        room1->north = room;
        room->south = room1;
        rooms[room1->ID] = room1;
        roomCount++;
    }
    displayRoom(room1);


    // save the layout to a file
    int saveStatus = saveLayout(layoutStateFPath, rooms, roomCount);
    if (saveStatus != EXIT_SUCCESS) {
        printf("Error saving layout to file.\n");
        return EXIT_FAILURE;
    }




    // Load the layout from the file
    Room** loadedRooms = NULL;
    int loadedRoomCount = 0;
    int loadedAllocRoomSize = 0;
    bool loadStatus = loadLayout(layoutStateFPath, &loadedRooms, &loadedRoomCount, &loadedAllocRoomSize);
    if (loadStatus != true) {
        printf("Error loading layout from file.\n");
        return EXIT_FAILURE;
    }

    // compare the loaded layout to what was saved
    if (loadedRoomCount != roomCount) {
        printf("Loaded room count does not match saved room count.\n");
        return EXIT_FAILURE;
    }

    printf("\nLoaded room count: %d\n", loadedRoomCount);
    displayRoom(loadedRooms[0]);
    displayRoom(loadedRooms[1]);

    // compare room 0
    if (loadedRooms[0]->ID != rooms[0]->ID ||
        loadedRooms[0]->north != NULL ||
        loadedRooms[0]->south == NULL ||
        loadedRooms[0]->west != NULL ||
        loadedRooms[0]->east != NULL) {
        printf("Loaded room 0 does not match saved room 0.\n");
        return EXIT_FAILURE;
    }
    // compare room 1
    if (loadedRooms[1]->ID != rooms[1]->ID ||
        loadedRooms[1]->north == NULL ||
        loadedRooms[1]->south != NULL ||
        loadedRooms[1]->west != NULL ||
        loadedRooms[1]->east != NULL) {
        printf("Loaded room 1 does not match saved room 1.\n");
        return EXIT_FAILURE;
    }
    // compare items in room 0
    ItemNode* currItem = loadedRooms[0]->items;
    ItemNode* currItem2 = rooms[0]->items;
    for (int i = 0; i < itemListCount(loadedRooms[0]->items); i++) {
        if (currItem == NULL) {
            printf("Loaded item %d in room 0 is NULL.\n", i);
            return EXIT_FAILURE;
        }
        if (currItem->data->ID != currItem2->data->ID) {
            printf("Loaded item %d in room 0 does not match saved item %d.\n", i, currItem2->data->ID);
            return EXIT_FAILURE;
        }
        currItem = currItem->next;
        currItem2 = currItem2->next;
    }
    // compare items in room 1
    currItem = loadedRooms[1]->items;
    currItem2 = rooms[1]->items;
    for (int i = 0; i < itemListCount(loadedRooms[1]->items); i++) {
        if (currItem == NULL) {
            printf("Loaded item %d in room 1 is NULL.\n", i);
            return EXIT_FAILURE;
        }
        if (currItem->data->ID != currItem2->data->ID) {
            printf("Loaded item %d in room 1 does not match saved item %d.\n", i, currItem2->data->ID);
            return EXIT_FAILURE;
        }
        currItem = currItem->next;
        currItem2 = currItem2->next;
    }
    // compare events in room 0
    EventNode* currEvent = loadedRooms[0]->events;
    EventNode* currEvent2 = rooms[0]->events;
    for (int i = 0; i < eventListCount(loadedRooms[0]->events); i++) {
        if (currEvent == NULL) {
            printf("Loaded event %d in room 0 is NULL.\n", i);
            return EXIT_FAILURE;
        }
        if (currEvent->data != currEvent2->data) {
            printf("Loaded event %d in room 0 does not match saved event %d.\n", i, currEvent2->data);
            return EXIT_FAILURE;
        }
        currEvent = currEvent->next;
        currEvent2 = currEvent2->next;
    }
    // compare events in room 1
    currEvent = loadedRooms[1]->events;
    currEvent2 = rooms[1]->events;
    for (int i = 0; i < eventListCount(loadedRooms[1]->events); i++) {
        if (currEvent == NULL) {
            printf("Loaded event %d in room 1 is NULL.\n", i);
            return EXIT_FAILURE;
        }
        if (currEvent->data != currEvent2->data) {
            printf("Loaded event %d in room 1 does not match saved event %d.\n", i, currEvent2->data);
            return EXIT_FAILURE;
        }
        currEvent = currEvent->next;
        currEvent2 = currEvent2->next;
    }





    // free memory
    freeRooms(&rooms, &roomCount);
    freeRooms(&loadedRooms, &loadedRoomCount);


    // compare the saved layout file to the expected layout file
    FILE* savedFile = fopen(layoutStateFPath, "r");
    FILE* expectedFile = fopen(expectedLayoutStateFPath, "r");
    if (savedFile == NULL || expectedFile == NULL) {
        printf("Error opening saved or expected layout file.\n");
        return EXIT_FAILURE;
    }
    char savedLine[256];
    char expectedLine[256];
    while (fgets(savedLine, sizeof(savedLine), savedFile) != NULL &&
           fgets(expectedLine, sizeof(expectedLine), expectedFile) != NULL) {
        if (strcmp(savedLine, expectedLine) != 0) {
            printf("Saved layout file does not match expected layout file.\n");
            fclose(savedFile);
            fclose(expectedFile);
            return EXIT_FAILURE;
        }
    }
    fclose(savedFile);
    fclose(expectedFile);
    printf("Saved layout file matches expected layout file.\n");

    printf("Test passed!\n");
    return EXIT_SUCCESS;    
}