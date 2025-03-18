#include "../include/dungeon.h"


void exploreDungeon(Room* currentRoom, Player* player){
    // if (currentRoom == NULL) {
    //     printf("You have reached a dead end!\n");
    //     return;
    // }
    printf("\n");
    displayRoom(currentRoom);

    // Room interactions (items, monsters, traps, etc)
    if (currentRoom->itemsCount > 0){
        int choice = parse_action_command();
        switch (choice){
            case SHOW:
                displayPlayerInventory(player);
                exploreDungeon(currentRoom, player);
                break;
            case PICKUP:
                printf("\nWhich item would you like to pick up?\n");
                int pickup_itemID = parse_item_command();
                if (pickup_itemID < 0 || pickup_itemID >= currentRoom->itemsCount){
                    printf("\nInvalid item ID");
                    exploreDungeon(currentRoom, player);
                    return;
                }
                pickUpItem(player, currentRoom->items[pickup_itemID]);
                exploreDungeon(currentRoom, player);
                break;
            case USE:
                printf("\nNot implemented yet");
                break;
            case DROP:
                printf("\nWhich item would you like to drop?\n");
                int drop_itemID = parse_item_command();
                if (drop_itemID < 0 || drop_itemID >= MAX_PLAYER_ITEMS || player->inventory[drop_itemID] == NULL){
                    printf("\nInvalid item ID");
                    exploreDungeon(currentRoom, player);
                    return;
                }
                dropItem(player, player->inventory[drop_itemID]);
                exploreDungeon(currentRoom, player);
                break;
            case MOVE:
                break;
            case EXIT:  
                printf("\nExiting dungeon");
                return;
            default:    
                printf("\nInvalid choice!\nEnter a valid choice");
                exploreDungeon(currentRoom, player);
                break;
        }
    }


    // Room movement
    printf("\n");
    int choice = parse_movement_command();
    switch(choice){
        case NORTH:
            if (currentRoom->north == NULL){
                printf("\nThere is no path on the north.");
                exploreDungeon(currentRoom, player);
                break;
            }
            exploreDungeon(currentRoom->north, player);
            break;
        case SOUTH:
            if (currentRoom->south == NULL){
                printf("\nThere is no path on the south.");
                exploreDungeon(currentRoom, player);
                return;
            }
            exploreDungeon(currentRoom->south, player);
            break;
        case WEST:
            if (currentRoom->west == NULL){
                printf("\nThere is no path on the west.");
                exploreDungeon(currentRoom, player);
                return;
            }
            exploreDungeon(currentRoom->west, player);
            break;
        case EAST:
            if (currentRoom->east == NULL){
                printf("\nThere is no path on the east.");
                exploreDungeon(currentRoom, player);
                return;
            }
            exploreDungeon(currentRoom->east, player);
            break;
        case EXIT:
            printf("\nExiting dungeon");
            return;
        default:
            printf("\nInvalid choice!\nEnter a valid choice");
            exploreDungeon(currentRoom, player);
            break;
    }

}