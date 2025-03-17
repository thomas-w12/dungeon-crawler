#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/room.h"
#include "../include/item.h"
#include "../include/player.h"


void moveNorth(Player* player, Room* currentRoom){
     
}

void moveSouth(Player* player, Room* currentRoom){

}

void moveWest(Player* player, Room* currentRoom){

}

void moveEast(Player* player, Room* currentRoom){

}

void pickUpItem(Player* player, Item item){

}

void loadPlayerState(FILE* f, Player* player){
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

void savePlayerState(FILE* f, Player player){

}