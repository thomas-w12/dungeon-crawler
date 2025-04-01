#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdbool.h>
#include "room.h"
#include "player.h"


void exploreDungeon(Room*** roomsPtr, int* roomsCount, int* allocRoomSize, Room* prevRoom, Room* currentRoom, Player* player, int** playerPathPtr, int* allocPathSize, int* playerPathCount);

#endif