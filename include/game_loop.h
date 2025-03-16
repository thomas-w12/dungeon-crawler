#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "room.h"

#define EXIT 0
#define NORTH 1
#define SOUTH 2
#define EAST 3
#define WEST 4

void game_loop();

int parse_command(char *input);

void execute_command(int command, Room *room);

#endif