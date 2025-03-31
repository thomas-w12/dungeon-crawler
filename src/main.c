#include <stdbool.h> // not sure if i should add this since it has already been included in dungeon.h
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

void loadGame(Room*** roomsPtr, int* roomCount, int noOfRooms, int* allocRoomSize, Player* player){
    char layoutStateFPath[] = {"saved_games/layoutState.txt"};
    char playerStateFPath[] = {"saved_games/playerState.txt"};

    generateLayout(roomsPtr, roomCount, noOfRooms, allocRoomSize);
}

void displayMainMenu(){
    printf("Main Menu Screen\nPress:\nL - load saved game\nT - Start a new game");
    char choice = getUserInputCommand();

    switch(choice){
        case LOAD:
            break;
        case SAVE:
            break;
        default:
            printf("Invalid command");
            displayMainMenu();
            break;
    }
}

int main() {
    srand(time(0));

    int allocRoomSize = 10; // initial rooms alloc size
    int roomCount = 0;
    Room** rooms = malloc(sizeof(Room*) * allocRoomSize);
    if (rooms == NULL){
        perror("Could not allocate memory for rooms");
        return EXIT_FAILURE;
    }
    
    char layoutStateFPath[] = {"saved_games/layoutState.txt"};
    char playerStateFPath[] = {"saved_games/playerState.txt"};
    
    generateLayout(&rooms, &roomCount, 20, &allocRoomSize);

    // expandRoom(&rooms, room, &roomCount, 10, &allocRoomSize);
    // loadLayout(layoutStateFPath, &rooms, &roomCount, &allocRoomSize);
    // displayRooms(rooms, roomCount);
    // saveLayout(layoutStateFPath, rooms, roomCount);

    // savePlayerState(playerStateFPath, player);
    // loadPlayerState(playerStateFPath, player);
   
    // displayRooms(rooms, roomCount);
    
    int* playerPath = malloc(sizeof(int)*roomCount);
    int allocPathSize = 0;
    int playerPathCount = 0;
    Player* player = Player_construct("Player", 0, 100, 0, NULL); // We need this store player inventory

    exploreDungeon(NULL, rooms[0], player, &playerPath, &allocPathSize, &playerPathCount);

    // saveLayout(layoutStateFPath, rooms, roomCount);
    // savePlayerState(playerStateFPath, player);

    // int arr[1000];
    // int numberOccurenceProbArr[] = {45, 40, 10, 5};
    // generateRandomIntArrProb(arr, 1000, 0, 3, numberOccurenceProbArr, 4);

    // for (int i=0; i<1000; i++){
    //     printf("\n%d", generateRandomInt(0, 3));
    // }

    free(playerPath);
    freeRooms(&rooms, &roomCount);
    freePlayer(player);
    // freeItemList(&itemsHead);

    return EXIT_SUCCESS;
}
    