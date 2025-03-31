#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdbool.h>
#include "room.h"
#include "player.h"


void exploreDungeon(Room* currentRoom, Player* player, bool isNewRoom);

#endif