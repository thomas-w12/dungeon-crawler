#ifndef DUNGEON_H
#define DUNGEON_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"
#include "player.h"
#include "command_parser.h"


void exploreDungeon(Room* currentRoom, Player* player, bool isNewRoom);

#endif