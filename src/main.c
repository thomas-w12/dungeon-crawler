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

// Give user feedback to let them know they cant pick duplicate items
// When player health is 0, display you died amd show main menu (Not sure if we should save state)
// Player can pick up duplicates but won't be validated (removed from room but not added to player inventory)
// Bug after falling in pit
// Should we show user available connections? N, S, W
// Should we give the user option to expand room?

bool loadGame(char* layoutStateFPath, char* playerStateFPath, Room*** roomsPtr, int* roomCount, int* allocRoomSize, Player** playerPtr){ // Need to check if there is a saved file and also if the saved file is empty or valid
    *playerPtr = Player_construct("Player", 0, 100, 0, NULL); 
    loadLayout(layoutStateFPath, roomsPtr, roomCount, allocRoomSize);
    loadPlayerState(playerStateFPath, *playerPtr);

    return true;
}

bool newGame(Room*** roomsPtr, int* roomCount, int noOfRooms, int* allocRoomSize, Player** playerPtr){
    char playerNameBuff[100];
    printf("Enter player name: ");
    scanf(" %99[^\n]", playerNameBuff);
    clearBuffer();

    generateLayout(roomsPtr, roomCount, noOfRooms, allocRoomSize);
    *playerPtr = Player_construct(playerNameBuff, 0, 100, 0, NULL); 

    return true;
}

void displayMainMenu(){
    printf("\nMain Menu Screen\nPress:\nL - Load saved game\nT - Start a new game\nQ - Quit the game\n");
}

int main() {
    srand(time(0));

    char layoutStateFPath[] = {"saved_games/layoutState.txt"};
    char playerStateFPath[] = {"saved_games/playerState.txt"};

    int allocRoomSize = 10; // initial rooms alloc size
    int roomCount = 0;
    Room** rooms = malloc(sizeof(Room*) * allocRoomSize);
    if (rooms == NULL){
        perror("Could not allocate memory for rooms\n");
        return EXIT_FAILURE;
    }
    
    int* playerPath = malloc(sizeof(int)*roomCount);
    if (playerPath == NULL){
        perror("Could not allocate memory for player path\n");
        return EXIT_FAILURE;
    }
    int allocPathSize = 0;
    int playerPathCount = 0;

    // expandRoom(&rooms, room, &roomCount, 10, &allocRoomSize);

    Player* player;
    while (true){
        displayMainMenu();
        char choice = getUserInputCommand();
        switch(choice){
            case LOAD_GAME:
                printf("Loading saved game...\n");
                loadGame(layoutStateFPath, playerStateFPath, &rooms, &roomCount, &allocRoomSize, &player);

                Room* prevRoom = NULL;
                exploreDungeon(NULL, rooms[player->currentRoom], player, &playerPath, &allocPathSize, &playerPathCount);
                break;
            case NEW_GAME:
                printf("Generating a new game...\n");
                newGame(&rooms, &roomCount, 20, &allocRoomSize, &player);
                exploreDungeon(NULL, rooms[0], player, &playerPath, &allocPathSize, &playerPathCount);
                break;
            case EXIT:
                printf("Quiting game...\n");
                return EXIT_SUCCESS;
            default:
                printf("Invalid command\n");
                displayMainMenu();
                break;
        }
    }

    // saveLayout(layoutStateFPath, rooms, roomCount);
    savePlayerState(playerStateFPath, player);
    free(playerPath);
    freeRooms(&rooms, &roomCount);
    freePlayer(player);

    return EXIT_SUCCESS;
}
    