#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/game_loop.h"

void game_loop() {
    char input[100];
    while (1) {
        printf("\nEnter a command: ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            printf("You entered: %s", input); // for debugging
            int command = parse_command(input);
            printf("Command: %d\n", command); // for debugging
            if (command == EXIT) {
                break;
            }
        } else {
            printf("Error reading input.");
        }
        printf("You entered: %s\n", input);
    }
}

int parse_command(char *input) {
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