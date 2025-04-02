#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/fileio.h"
#include "../include/room.h"
#include "../include/player.h"
#include "../include/item.h"
#include "../include/dungeon.h"
#include "../include/event.h"
#include "../include/global.h"


bool loadGame(char* layoutStateFPath, char* playerStateFPath, Room*** roomsPtr, int* roomCount, int* allocRoomSize, Player* player){ // Need to check if there is a saved file and also if the saved file is empty or valid
    bool status = true;
    
    status &= loadLayout(layoutStateFPath, roomsPtr, roomCount, allocRoomSize);
    status &= loadPlayerState(playerStateFPath, player);
    
    return status;
}

bool newGame(Room*** roomsPtr, int* roomCount, int noOfRooms, int* allocRoomSize, Player** playerPtr){
    char playerNameBuff[100];
    printf("Enter player name: ");
    scanf(" %99[^\n]", playerNameBuff);
    clearBuffer();

    generateLayout(roomsPtr, roomCount, noOfRooms, allocRoomSize);
    freePlayer(*playerPtr);
    *playerPtr = Player_construct(playerNameBuff, 0, 100, 0, NULL);

    return true;
}

bool resetParams(Room*** roomsPtr, int* roomCount, int* allocRoomSize, int** playerPathPtr, int*allocPathSize , int* playerPathCount, Player** playerPtr){
    if (*roomCount > 0){
        free(*playerPathPtr);
        freeRooms(roomsPtr, roomCount);
        freePlayer(*playerPtr);

        *allocRoomSize = 10;
        *roomCount = 0;
        *roomsPtr = malloc(sizeof(Room*) * (*allocRoomSize));
        if (*roomsPtr == NULL){
            perror("Could not allocate memory for rooms\n");
            return false;
        }
        
        *playerPathPtr = malloc(sizeof(int) * (*allocRoomSize));
        if (*playerPathPtr == NULL){
            perror("Could not allocate memory for player path\n");
            return false;
        }
        *allocPathSize = 0;
        *playerPathCount = 0;

        *playerPtr = Player_construct("Player", 0, 100, 0, NULL);
    }
    return true;
}

void displayMainMenu(){
    printf("\nMain Menu Screen\nPress:\nL - Load saved game\nT - Start a new game\nQ - Quit the game\n");
}

int main() {
    srand(time(0));

    char layoutStateFPath[] = {"saved_games/layoutState.txt"};
    char playerStateFPath[] = {"saved_games/playerState.txt"};

    int allocRoomSize = INITIAL_NO_OF_ROOMS; // initial rooms alloc size
    int roomCount = 0;
    Room** rooms = malloc(sizeof(Room*) * allocRoomSize);
    if (rooms == NULL){
        perror("Could not allocate memory for rooms\n");
        return EXIT_FAILURE;
    }
    
    int* playerPath = malloc(sizeof(int)*allocRoomSize);
    if (playerPath == NULL){
        perror("Could not allocate memory for player path\n");
        return EXIT_FAILURE;
    }
    int allocPathSize = 0;
    int playerPathCount = 0;

    Player* player = Player_construct("Player", 0, 100, 0, NULL); 
    bool exitGame = false;
    while (!exitGame){
        displayMainMenu();
        char choice = getUserInputCommand();
        switch(choice){
            case LOAD_GAME:{
                printf("Loading saved game...\n");
                if (resetParams(&rooms, &roomCount, &allocRoomSize, &playerPath, &allocPathSize, &playerPathCount, &player) == false) return EXIT_FAILURE;

                if (loadGame(layoutStateFPath, playerStateFPath, &rooms, &roomCount, &allocRoomSize, player) == false) {
                    printf("There was an error loading the saved game!\n");
                    exitGame = true;
                    break;
                }

                Room* prevRoom = NULL;
                exploreDungeon(&rooms, &roomCount, &allocRoomSize, prevRoom, rooms[player->currentRoom], player, &playerPath, &allocPathSize, &playerPathCount);
                break;
            }
            case NEW_GAME:
                printf("Generating a new game...\n");
                if (resetParams(&rooms, &roomCount, &allocRoomSize, &playerPath, &allocPathSize, &playerPathCount, &player) == false) return EXIT_FAILURE;
                
                newGame(&rooms, &roomCount, INITIAL_NO_OF_ROOMS, &allocRoomSize, &player);
                
                exploreDungeon(&rooms, &roomCount, &allocRoomSize, NULL, rooms[0], player, &playerPath, &allocPathSize, &playerPathCount);
                break;
            case EXIT:
                printf("Quiting game...\n");
                exitGame = true;
                break;
            default:
                printf("Invalid command\n");
                displayMainMenu();
                break;
        }
    }

    saveLayout(layoutStateFPath, rooms, roomCount);
    savePlayerState(playerStateFPath, player);

    free(playerPath);
    freeRooms(&rooms, &roomCount);
    freePlayer(player);

    return EXIT_SUCCESS;
}
    