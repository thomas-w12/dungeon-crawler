#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/room.h"
#include "../include/item.h"
#include "../include/player.h"


Player* Player_construct(char* name, int currentRoom, int health, int score, Room* currentRoomPtr){
    Player* player = (Player*)malloc(sizeof(Player));
    if (player == NULL){
        printf("\nCould not create player");
        return NULL;
    }

    strcpy(player->name, name);
    player->currentRoom = currentRoom;
    player->health = health;
    player->score = score;
    player->itemsCount = 0;

    for (int i=0; i<MAX_PLAYER_ITEMS; i++){
        player->inventory[i] = NULL;
    }

    player->currentRoomPtr = currentRoomPtr;

    return player;
}

void displayPlayer(Player* player){
    printf("\nPlayer - Name: %s\tCurrent Room: %d\tHealth: %d\tScore: %d", player->name, player->currentRoom, player->health, player->score);
    displayPlayerInventory(player);
}

void displayPlayerInventory(Player* player){
    printf("\nItems in inventory (%d): ", player->itemsCount);
    displayItems(player->inventory, player->itemsCount, MAX_PLAYER_ITEMS);
}

void updatePlayerRoom(Player* player, Room* currentRoom){
    player->currentRoom = currentRoom->ID;
    player->currentRoomPtr = currentRoom;
}

void pickUpItem(Player* player, int pickupItemID){
    Item* pickupTargetItem = NULL;

    // Find the item with matching ID in the current room
    for (int i = 0; i < player->currentRoomPtr->itemsCount; i++) {
        if (
            player->currentRoomPtr->items[i] != NULL && 
            player->currentRoomPtr->items[i]->ID == pickupItemID
        ) {
            pickupTargetItem = player->currentRoomPtr->items[i];
            break;
        }
    }
    if (pickupTargetItem == NULL) {
        printf("\nInvalid item ID\n");
        return;
    }

    if (player->itemsCount >= MAX_PLAYER_ITEMS){
        printf("\nInventory is full. Cannot pick up item.");
        return;
    }

    player->inventory[player->itemsCount] = pickupTargetItem;
    player->itemsCount++;

    // Remove item from room, make sure item that is passed is in the current room
    for (int i=0; i<player->currentRoomPtr->itemsCount; i++){
        if (player->currentRoomPtr->items[i] == pickupTargetItem){
            player->currentRoomPtr->items[i] = NULL;
            player->currentRoomPtr->itemsCount--;
            break;
        }
    }
}

void dropItem(Player* player, int dropItemID){
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
        return;
    }
    if (player->itemsCount == 0){
        printf("\nInventory is empty. Cannot drop item.");
        return;
    }

    for (int i=0; i<player->itemsCount; i++){
        if (player->inventory[i] == dropTargetItem){
            player->inventory[i] = NULL;
            player->itemsCount--;
            break;
        }
    }

    // Add item to room
    for (int i=0; i<MAX_ITEMS_IN_ROOM; i++){
        if (player->currentRoomPtr->items[i] == NULL){
            player->currentRoomPtr->items[i] = dropTargetItem;
            player->currentRoomPtr->itemsCount++;
            break;
        }
    }
}

void decreasePlayerHealth(Player* player, int damage){
    player->health -= damage;
}

void increasePlayerHealth(Player* player, int health){
    player->health += health;
}

void increasePlayerScore(Player* player, int score){
    player->score += score;
}

void freePlayer(Player* player){
    // freeItems(player->inventory, &player->itemsCount);
    free(player);
}

