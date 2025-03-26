#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "item.h"
#include "room.h"

#define MAX_PLAYER_ITEMS 3

typedef struct Player {
    char name[10]; // Tell player to enter name at begining. Max length of about 10 characters
    int currentRoom; //ID of current room
    Room* currentRoomPtr; // Pointer to current room
    int health; // Health bar
    int score;
    Item* inventory[MAX_PLAYER_ITEMS]; // List of items the player has
    int itemsCount;
} Player;

Player* Player_construct(char* name, int currentRoom, int health, int score, Room* currentRoomPtr);
void displayPlayer(Player* player);
void displayPlayerInventory(Player* player);
void updatePlayerRoom(Player* player, Room* currentRoom);
void pickUpItem(Player* player, int pickupItemID);
void dropItem(Player* player, int dropItemID);
void decreasePlayerHealth(Player* player, int damage);
void increasePlayerHealth(Player* player, int health);
void increasePlayerScore(Player* player, int score);
void freePlayer(Player* player);

#endif