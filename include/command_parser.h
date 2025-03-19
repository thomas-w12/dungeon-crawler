#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"

#define EXIT 0
#define NORTH 1
#define SOUTH 2
#define EAST 3
#define WEST 4
#define PICKUP 6
#define USE 7
#define DROP 8
#define INVENTORY 9

int parse_room_command();

int parse_item_command();

#endif