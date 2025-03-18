#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/command_parser.h"

int parse_movement_command() {
    char* input[100];
    printf("\nWhere would you like to go?\nN - go north\nS - go south\nW - go west\nE - go east\nQ - quit\n");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1; // Error reading input
    }
    if (strcmp(input, "Q\n") == 0 || strcmp(input, "q\n") == 0) {
        return EXIT;
    } else if (strcmp(input, "N\n") == 0 || strcmp(input, "n\n") == 0) {
        return NORTH;
    } else if (strcmp(input, "S\n") == 0 || strcmp(input, "s\n") == 0) {
        return SOUTH;
    } else if (strcmp(input, "E\n") == 0 || strcmp(input, "e\n") == 0) {
        return EAST;
    } else if (strcmp(input, "W\n") == 0 || strcmp(input, "w\n") == 0) {
        return WEST;
    } else {
        return -1; // Invalid command
    }
}