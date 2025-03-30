#include "../include/dungeon.h"

void displayMenuScreen(Room* currentRoom){
    displayRoom(currentRoom);

    printf("\nWhat would you like to do?\nP - pick up item\nU - use item\nD - drop item\nI - show inventory\nN - go north\nS - go south\nW - go west\nE - go east\nQ - quit\n");
}


void exploreDungeon(Room* currentRoom, Player* player, bool isNewRoom){ // Maybe use displayRoom
    triggerEvent(currentRoom, player);
    // Update player's current room
    updatePlayerRoom(player, currentRoom);
    if (isNewRoom == true){
        displayMenuScreen(currentRoom);
        //add roomId to path
    }

    char choice;
    scanf(" %c", &choice);
    choice = (char) toupper((int) choice);
    // printf("\nChoice: %c", choice);

    switch (choice) {
        case INVENTORY:
            displayPlayerInventory(player);
            printf("\n");
            exploreDungeon(currentRoom, player, false);
            // continue in same room
            break;
        case PICKUP:
            // if there is an item in the room
            if (itemListCount(currentRoom->items) == 0){
                printf("\nThere are no items to pick up.\n");
                exploreDungeon(currentRoom, player, false);
                break;
            }
            printf("\nEnter the item ID to pick up:\n");
            int pickupItemID = parse_item_command();
            pickUpItem(player, pickupItemID);
            displayMenuScreen(currentRoom);
            exploreDungeon(currentRoom, player, false); // would like to redisplay room
            break;
        case USE:
            printf("\nNot implemented yet");
            exploreDungeon(currentRoom, player, false);
            break;
        case DROP:
            if (itemListCount(player->inventory) == 0){
                printf("\nThere are no items in your inventory.\n");
                exploreDungeon(currentRoom, player, false);
                break;
            }
            printf("\nEnter the item ID to drop:\n");
            int dropItemID = parse_item_command();
            dropItem(player, dropItemID);
            displayMenuScreen(currentRoom);
            exploreDungeon(currentRoom, player, false);
            break;
        case NORTH: // If there is no path and already traversed path includes 90% of the room count the expand current room to create more path
            if (currentRoom->north == NULL) {
                printf("\nThere is no path on the north.\n");
                exploreDungeon(currentRoom, player, false);
                break;;
            }
            printf("\nMoving to the north\n");
            // currentRoom = currentRoom->north; // Maybe remove this and put directly in exploredungeon🤔💭?
            exploreDungeon(currentRoom->north, player, true);
            break;
        case SOUTH:
            if (currentRoom->south == NULL) {
                printf("\nThere is no path on the south.\n");
                exploreDungeon(currentRoom, player, false);
                break;
            }
            printf("\nMoving to the south\n");
            // currentRoom = currentRoom->south;
            exploreDungeon(currentRoom->south, player, true);
            break;
        case WEST:
            if (currentRoom->west == NULL) {
                printf("\nThere is no path on the west.\n");
                exploreDungeon(currentRoom, player, false);
                break;
            }
            printf("\nMoving to the west\n");
            // currentRoom = currentRoom->west;
            exploreDungeon(currentRoom->west, player, true);
            break;
        case EAST:
            if (currentRoom->east == NULL) {
                printf("\nThere is no path on the east.\n");
                exploreDungeon(currentRoom, player, false);
                break;
            }
            printf("\nMoving to the east\n");
            // currentRoom = currentRoom->east;
            exploreDungeon(currentRoom->east, player, true);
            break;
        case EXIT:
            printf("\nExiting dungeon\n");
            return;
        default:
            printf("\nInvalid choice!\nEnter a valid choice\n");
            exploreDungeon(currentRoom, player, false);
            break;
    }
}


