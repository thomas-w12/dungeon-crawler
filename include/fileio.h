#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdbool.h>
#include "room.h"
#include "player.h"

int saveLayout(const char* layoutStateFPath, Room** rooms, int roomCount);
bool loadLayout(const char* layoutStateFPath, Room*** roomsPtr, int* roomCount, int* allocRoomSize);
int savePlayerState(const char* playerStateFPath, Player* player);
bool loadPlayerState(const char* playerStateFPath, Player* player);

#endif
