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
#define PICKUP 5
#define USE 6
#define DROP 7
#define SHOW 8
#define MOVE 9

int parse_movement_command();

int parse_action_command();

int parse_item_command();

#endif