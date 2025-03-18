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

void moveNorth(Player* player, Room* currentRoom);
void moveSouth(Player* player, Room* currentRoom);
void moveWest(Player* player, Room* currentRoom);
void moveEast(Player* player, Room* currentRoom);
void pickUpItem(Player* player, Item* item);

#endif