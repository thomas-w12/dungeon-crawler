#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "item.h"
#include "room.h"
// struct Room;

#define MAX_PLAYER_ITEMS 3

typedef struct Player {
    char name[10]; // Tell player to enter name at begining. Max length of about 10 characters
    int currentRoom; //ID of current room
    int health; // Health bar
    int score;
    Item* inventory[MAX_PLAYER_ITEMS]; // List of items the player has
    int itemsCount;
} Player;

Player* Player_construct(char* name, int currentRoom, int health, int score);
void displayPlayer(Player* player);
void displayPlayerInventory(Player* player);
void updatePlayerRoom(Player* player, Room* currentRoom);
void pickUpItem(Player* player, Item* item);

void freePlayer(Player* player);

#endif