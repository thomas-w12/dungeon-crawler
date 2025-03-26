#include "../include/command_parser.h"

int parse_room_command() {
    // char* input[100];
    printf("\nWhat would you like to do?\nP - pick up item\nU - use item\nD - drop item\nI - show inventory\nN - go north\nS - go south\nW - go west\nE - go east\nQ - quit\n");
    // if (fgets(input, sizeof(input), stdin) == NULL) {
    //     return -1; // Error reading input
    // }
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
            return -1; // Invalid command
    }
    // if (strcmp(input, "Q\n") == 0 || strcmp(input, "q\n") == 0) {
    //     return EXIT;
    // } else if (strcmp(input, "P\n") == 0 || strcmp(input, "p\n") == 0) {
    //     return PICKUP;
    // } else if (strcmp(input, "U\n") == 0 || strcmp(input, "u\n") == 0) {
    //     return USE;
    // } else if (strcmp(input, "D\n") == 0 || strcmp(input, "d\n") == 0) {
    //     return DROP;
    // } else if (strcmp(input, "I\n") == 0 || strcmp(input, "i\n") == 0) {
    //     return INVENTORY;
    // } else if (strcmp(input, "N\n") == 0 || strcmp(input, "n\n") == 0) {
    //     return NORTH;
    // } else if (strcmp(input, "S\n") == 0 || strcmp(input, "s\n") == 0) {
    //     return SOUTH;
    // } else if (strcmp(input, "E\n") == 0 || strcmp(input, "e\n") == 0) {
    //     return EAST;
    // } else if (strcmp(input, "W\n") == 0 || strcmp(input, "w\n") == 0) {
    //     return WEST;
    // } else {
    //     return -1; // Invalid command
    // }
}

int parse_item_command() {
    // char* input[100];
    // if (fgets(input, sizeof(input), stdin) == NULL) {
    //     return -1; // Error reading input
    // }
    int input;
    scanf(" %d", &input);
    printf("Item Input: %d", input);
    return input;
    // return strtol(input, NULL, 10);
}