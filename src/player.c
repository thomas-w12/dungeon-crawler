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

    player->name = strdup(name);
    if (player->name == NULL){
        printf("\nCould not create player name");
        free(player);
        return NULL;
    }
    player->currentRoom = currentRoom;
    player->health = health;
    player->score = score;
    
    player->inventory = NULL;
    player->currentRoomPtr = currentRoomPtr;

    return player;
}

void displayPlayer(Player* player){
    printf("\nPlayer - Name: %s\tCurrent Room: %d\tHealth: %d\tScore: %d", player->name, player->currentRoom, player->health, player->score);
    displayPlayerInventory(player);
}

void displayPlayerInventory(Player* player){
    printf("\nItems in inventory (%d): ", itemListCount(player->inventory));
    printItemList(player->inventory);
}

void updatePlayerRoom(Player* player, Room* currentRoom){
    player->currentRoom = currentRoom->ID;
    player->currentRoomPtr = currentRoom;
}

void pickUpItem(Player* player, int pickupItemID){
    if (itemListCount(player->inventory) >= MAX_PLAYER_ITEMS){
        printf("\nInventory is full. Cannot pick up item.");
        return;
    }

    // Find the item with matching ID in the current room
    Item* pickupTargetItem = ItemList_deleteItemID(&player->currentRoomPtr->items, pickupItemID);
    if (pickupTargetItem == NULL) {
        printf("\nInvalid item ID\n");
        return;
    }

    // Add item to player inventory
    ItemList_insert(&player->inventory, pickupTargetItem);
}

void dropItem(Player* player, int dropItemID){
    if (itemListCount(player->inventory) == 0){
        printf("\nInventory is empty. Cannot drop item.");
        return;
    }

    // Find the item with matching ID in the player's inventory
    Item* dropTargetItem = ItemList_deleteItemID(&player->inventory, dropItemID);

    if (dropTargetItem == NULL) {
        printf("\nInvalid item ID\n");
        return;
    }

    // Add item to room
    ItemList_insert(&player->currentRoomPtr->items, dropTargetItem);
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
    if (player == NULL){
        return;
    }
    free(player->name);
    freeItemList(&player->inventory);
    free(player);
}

