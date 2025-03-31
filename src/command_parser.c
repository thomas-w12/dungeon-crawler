#include "../include/command_parser.h"
#include "../include/global.h"
#include <ctype.h>


void clearBuffer(){
    while (getchar() != '\n');
}

char getUserInputCommand() {
    char input;
    scanf(" %c", &input);
    input = (char) toupper((int) input);
    clearBuffer();

    return input;
}

int parse_item_command() {
    int input;

    if (scanf("%d", &input) != 1){
        clearBuffer();
        return -2; // using -2 to represent an invalid command
    };
    clearBuffer();

    return input;
}