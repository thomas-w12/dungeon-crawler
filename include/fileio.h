#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include "room.h"
#include "player.h"

#define DNE -1

int saveLayout(const char* layoutStateFPath, Room** rooms, int roomCount);
int loadLayout(const char* layoutStateFPath, Room** rooms, int* roomCount);
int savePlayerState(const char* playerStateFPath, Player* player);
int loadPlayerState(const char* playerStateFPath, Player* player);

#endif
