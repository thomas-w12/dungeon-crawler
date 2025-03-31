#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"

typedef enum Commands{
    EXIT = 'Q',
    NORTH = 'N',
    SOUTH = 'S',
    EAST = 'E',
    WEST = 'W',
    PICKUP = 'P',
    USE = 'U',
    DROP = 'D',
    INVENTORY = 'I',
    ACCEPT = 'A',
    DECLINE = 'X',
    LOAD_GAME = 'L',
    NEW_GAME = 'T',
    ROOM = 'R', // Display room details
    PLAYER_STATS = 'M' // Display player stats
} Commands;

void clearBuffer();
char getUserInputCommand();
int parse_item_command();

#endif