#include "../include/command_parser.h"
#include "../include/global.h"
#include <ctype.h>


int parse_room_command() {
    // char* input[100];
    printf("\nWhat would you like to do?\nP - pick up item\nU - use item\nD - drop item\nI - show inventory\nN - go north\nS - go south\nW - go west\nE - go east\nQ - quit\n");

    char input;
    scanf(" %c", &input);
    switch (input){
        case 'Q':
        case 'q':
            return EXIT;
        case 'P':
        case 'p':
            return PICKUP;
        case 'U':
        case 'u':
            return USE;
        case 'D':
        case 'd':
            return DROP;
        case 'I':
        case 'i':
            return INVENTORY;
        case 'N':
        case 'n':
            return NORTH;
        case 'S':
        case 's':
            return SOUTH;
        case 'E':
        case 'e':
            return EAST;
        case 'W':
        case 'w':
            return WEST;
        default:
            return DNE; // Invalid command
    }
}

char getUserInputCommand() { // Have to think of how to handle unexpected input like int or str
    char input;
    scanf(" %c", &input);
    input = (char) toupper((int) input);

    return input;
}

int parse_item_command() {
    int input;
    scanf(" %d", &input);

    return input;
}