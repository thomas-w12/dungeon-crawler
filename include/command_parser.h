#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"

// #define EXIT 0
// #define NORTH 1
// #define SOUTH 2
// #define EAST 3
// #define WEST 4
// #define PICKUP 6
// #define USE 7
// #define DROP 8
// #define INVENTORY 9


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
} Commands;

int parse_room_command();

int parse_item_command();

#endif