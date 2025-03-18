#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/room.h"
#include "../include/item.h"
#include "../include/player.h"


Player* Player_construct(char* name, int currentRoom, int health, int score){
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

    return player;
}

void displayPlayer(Player* player){
    printf("\nPlayer - Name: %s\tCurrent Room: %d\tHealth: %d\tScore: %d", player->name, player->currentRoom, player->health, player->score);
    displayPlayerInventory(player);
}

void displayPlayerInventory(Player* player){
    printf("\nItems in inventory (%d): ", player->itemsCount);
    displayItems(player->inventory, player->itemsCount);
}

void updatePlayerRoom(Player* player, Room* currentRoom){
    player->currentRoom = currentRoom->ID;
}

void pickUpItem(Player* player, Item* item){
    if (player->itemsCount >= MAX_PLAYER_ITEMS){
        printf("\nInventory is full. Cannot pick up item.");
        return;
    }

    player->inventory[player->itemsCount] = item;
    player->itemsCount++;
}

void freePlayer(Player* player){
    freeItems(player->inventory, &player->itemsCount);
    free(player);
}

