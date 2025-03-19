#include "../include/dungeon.h"

void exploreDungeon(Room* currentRoom, Player* player) {
    while (1) {
        // Display current room
        displayRoom(currentRoom);
        // Update player's current room
        updatePlayerRoom(player, currentRoom);

        int choice = parse_room_command();

        switch (choice) {
            case INVENTORY:
                displayPlayerInventory(player);
                printf("\n");
                // continue in same room
                continue;
            case PICKUP:
                printf("\nEnter the item ID to pick up:\n");
                int pickupItemID = parse_item_command();
                Item* pickupTargetItem = NULL;

                // Find the item with matching ID in the current room
                for (int i = 0; i < currentRoom->itemsCount; i++) {
                    if (currentRoom->items[i] != NULL 
                        && currentRoom->items[i]->ID == pickupItemID) {
                            pickupTargetItem = currentRoom->items[i];
                        break;
                    }
                }
                if (pickupTargetItem == NULL) {
                    printf("\nInvalid item ID\n");
                    continue;
                }
                pickUpItem(player, pickupTargetItem);
                continue;
            case USE:
                printf("\nNot implemented yet");
                continue;
            case DROP:
                printf("\nEnter the item ID to drop:\n");
                int dropItemID = parse_item_command();
                Item* dropTargetItem = NULL;

                // Find the item with matching ID in the player's inventory
                for (int i = 0; i < player->itemsCount; i++) {
                    if (player->inventory[i] != NULL 
                        && player->inventory[i]->ID == dropItemID) {
                            dropTargetItem = player->inventory[i];
                        break;
                    }
                }
                if (dropTargetItem == NULL) {
                    printf("\nInvalid item ID\n");
                    continue;
                }
                dropItem(player, dropTargetItem);
                continue;
            case NORTH:
                if (currentRoom->north == NULL) {
                    printf("\nThere is no path on the north.\n");
                    continue;
                }
                printf("\nMoving to the north\n");
                currentRoom = currentRoom->north;
                break;
            case SOUTH:
                if (currentRoom->south == NULL) {
                    printf("\nThere is no path on the south.\n");
                    continue;
                }
                printf("\nMoving to the south\n");
                currentRoom = currentRoom->south;
                break;
            case WEST:
                if (currentRoom->west == NULL) {
                    printf("\nThere is no path on the west.\n");
                    continue;
                }
                printf("\nMoving to the west\n");
                currentRoom = currentRoom->west;
                break;
            case EAST:
                if (currentRoom->east == NULL) {
                    printf("\nThere is no path on the east.\n");
                    continue;
                }
                printf("\nMoving to the east\n");
                currentRoom = currentRoom->east;
                break;
            case EXIT:
                printf("\nExiting dungeon\n");
                return;
            default:
                printf("\nInvalid choice!\nEnter a valid choice\n");
                continue;
        }
    }
}


