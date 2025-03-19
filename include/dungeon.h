#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"
#include "player.h"
#include "command_parser.h"

int roomInteraction(Room* currentRoom, Player* player);
int moveRooms(Room* currentRoom, Player* player);

void exploreDungeon(Room* currentRoom, Player* player);

#endif