#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdbool.h>
#include "room.h"
#include "player.h"


void exploreDungeon(Room* prevRoom, Room* currentRoom, Player* player, int** playerPathPtr, int* allocPathSize, int* playerPathCount);

#endif