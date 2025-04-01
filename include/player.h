#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "item.h"
#include "room.h"

#define MAX_PLAYER_ITEMS 3
#define MAX_PLAYER_NAME_LENGTH 100

typedef struct Player {
    char name[100]; 
    int currentRoom; //ID of current room (This is redundant)
    Room* currentRoomPtr; // Pointer to current room
    int health; // Health bar
    int score;
    ItemNode* inventory; // List of items the player has
} Player;

Player* Player_construct(char* name, int currentRoom, int health, int score, Room* currentRoomPtr);
void displayPlayer(Player* player);
void displayPlayerInventory(Player* player);
void updatePlayerRoom(Player* player, Room* currentRoom);
void pickUpItem(Player* player, int pickupItemID);
void dropItem(Player* player, int dropItemID);
bool useItem(Player* player, int itemID);
void decreasePlayerHealth(Player* player, int damage);
void increasePlayerHealth(Player* player, int health);
void increasePlayerScore(Player* player, int score);
bool triggerEvent(Room* room, Player* player, Event currEvent);
bool triggerEvents(Room* room, Player* player);
void freePlayer(Player* player);

#endif