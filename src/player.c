#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/room.h"
#include "../include/item.h"
#include "../include/player.h"


void moveNorth(Player* player, Room* currentRoom){
    (void)player;
    (void)currentRoom;
}

void moveSouth(Player* player, Room* currentRoom){

}

void moveWest(Player* player, Room* currentRoom){

}

void moveEast(Player* player, Room* currentRoom){

}

void pickUpItem(Player* player, Item item){

}

int loadPlayerState(const char* playerStateFPath, Player* player) {
    char line[100];
    fscanf(f, "%s", line);
    char* token = strtok(line, ",");

    int index = 0;
    while (token != NULL){
        switch(index){
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
        }

        token = strtok(NULL, ",");
        index ++;
    }

}
// int loadPlayerState(const char* playerStateFPath, Player* player) {
//     printf("Loading player state from: %s\n", playerStateFPath);  // Debugging output
//     return loadPlayerState(playerStateFPath, player);  // Calls function from `fileio.c`
// }

int savePlayerState(const char* playerStateFPath, Player* player) {
    FILE* f = fopen(playerStateFPath, "w");
    if (f == NULL) {
        perror("Error opening player state file");
        return EXIT_FAILURE;
    }
    fprintf(f, "%s,%d,", player->name, player->currentRoom);
    fclose(f);
}

