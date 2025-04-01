#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dungeon.h"
#include "../include/command_parser.h"

void displayRoomMenuScreen(){
    printf("What would you like to do?\nP - pick up item\nU - use item\nD - drop item\nI - show inventory\nN - go north\nS - go south\nW - go west\nE - go east\nR - display room menu\nM - show player stats\nQ - quit\n");
}

void printPlayerPath(int* playerPath, int playerPathCount){
    printf("Player path count: %d\n", playerPathCount);
    for (int i=0; i<playerPathCount; i++){
        printf("%d->", playerPath[i]);
    }
    printf("\n");
}

void expand(Room*** roomsPtr, Room* room, int* allocRoomSize, int* roomsCount, int playerPathCount){
    int connections = 0;
    connections += (room->north == NULL ? 0 : 1);
    connections += (room->south == NULL ? 0 : 1);
    connections += (room->west == NULL ? 0 : 1);
    connections += (room->east == NULL ? 0 : 1);

    // If player is at a dead end and has traversed at least 30% of the total rooms
    if ((connections <= 1) && ((float) (playerPathCount) > (float) (*roomsCount * 0.3))){
        printf("Expanding room. Connections: %d. Traversed count: %d\n", connections, playerPathCount);
        expandRoom(roomsPtr, room, roomsCount, EXPAND_ROOM_COUNT, allocRoomSize);
    }
}

void exploreDungeon(Room*** roomsPtr, int* roomsCount, int* allocRoomSize, Room* prevRoom, Room* currentRoom, Player* player, int** playerPathPtr, int* allocPathSize, int* playerPathCount){
    if (player->health <= 0){
        printf("You are dead. Game over.\n");
        return;
    }

    // Assumption that there would be zero events in the entry room
    if ((prevRoom == NULL) || (prevRoom->ID != currentRoom->ID)){
        printf("\n");
        displayRoom(currentRoom);
        if (triggerEvents(currentRoom, player) == false) {
            exploreDungeon(roomsPtr, roomsCount, allocRoomSize, prevRoom, prevRoom, player, playerPathPtr, allocPathSize, playerPathCount);
            return;
        }

        if (*playerPathCount >= *allocPathSize){
            int* newPtr = realloc(*playerPathPtr, (*allocPathSize+50));
            if (newPtr == NULL){
                printf("Could not reallocate memory for player path\n");
                return;
            }
            *playerPathPtr = newPtr;
            *allocPathSize += 50;
        }
        (*playerPathPtr)[*playerPathCount] = currentRoom->ID;
        (*playerPathCount)++;

        // printPlayerPath(*playerPathPtr, *playerPathCount);
        displayRoomMenuScreen();
    }

    // Update player's current room
    updatePlayerRoom(player, currentRoom);

    char choice = getUserInputCommand();
    // printf("\nChoice: %c", choice);
    Room* nextRoom = currentRoom;
    switch (choice) {
        case ROOM:
            printf("\n");
           displayRoom(currentRoom);
           displayRoomMenuScreen();
           break;
        case PLAYER_STATS:
            displayPlayer(player);
            break;
        case INVENTORY:
            displayPlayerInventory(player);
            break;
        case PICKUP:{
            if (itemListCount(currentRoom->items) == 0){
                printf("There are no items to pick up.\n");
                break;
            }
            printf("Enter the item ID to pick up: ");
            int pickupItemID = parse_item_command();
            pickUpItem(player, pickupItemID);

            printf("\n");
            displayRoom(currentRoom);
            displayRoomMenuScreen(currentRoom);
            break;
        }
        case USE:{
            if (itemListCount(player->inventory) == 0){ // Redundant, should remove
                printf("Inventory is empty. There is no item to use.\n");
                return;
            }
            
            printf("Enter the item ID to use: ");
            int useItemID = parse_item_command();
            useItem(player, useItemID);
            break;
        }
        case DROP:{
            if (itemListCount(player->inventory) == 0){
                printf("There are no items in your inventory.\n");
                break;
            }
            printf("Enter the item ID to drop: ");
            int dropItemID = parse_item_command();
            dropItem(player, dropItemID);

            printf("\n");
            displayRoom(currentRoom);
            displayRoomMenuScreen(currentRoom);
            break;
        }
        case NORTH: // If there is no path and already traversed path includes 90% of the room count the expand current room to create more path
            if (currentRoom->north == NULL) {
                printf("There is no path on the north.\n");
                expand(roomsPtr, currentRoom, allocRoomSize, roomsCount, *playerPathCount);
                break;;
            }
            printf("Moving to the north\n");
            nextRoom = currentRoom->north;
            break;
        case SOUTH:
            if (currentRoom->south == NULL) {
                printf("There is no path on the south.\n");
                expand(roomsPtr, currentRoom, allocRoomSize, roomsCount, *playerPathCount);
                break;
            }
            printf("Moving to the south\n");
            nextRoom = currentRoom->south;
            break;
        case WEST:
            if (currentRoom->west == NULL) {
                printf("There is no path on the west.\n");
                expand(roomsPtr, currentRoom, allocRoomSize, roomsCount, *playerPathCount);
                break;
            }
            printf("Moving to the west\n");
            nextRoom = currentRoom->west;
            break;
        case EAST:
            if (currentRoom->east == NULL) {
                printf("There is no path on the east.\n");
                expand(roomsPtr, currentRoom, allocRoomSize, roomsCount, *playerPathCount);
                break;
            }
            printf("Moving to the east\n");
            nextRoom = currentRoom->east;
            break;
        case EXIT:
            printf("Exiting dungeon\n");
            return;
        default:
            printf("Invalid choice!\nEnter a valid choice\n");
            break;
    }
    exploreDungeon(roomsPtr, roomsCount, allocRoomSize, currentRoom, nextRoom, player, playerPathPtr, allocPathSize, playerPathCount);
}