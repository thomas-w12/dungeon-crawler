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

    // Item* item1 = Item_construct(0);
    // Item* item2 = Item_construct(1);
    // Item* item3 = Item_construct(2);
    // Item* item4 = Item_construct(3);

    // ItemNode* itemsHead = NULL;
    // ItemList_insert(&itemsHead, item1);
    // ItemList_insert(&itemsHead, item2);
    // ItemList_insert(&itemsHead, item3);
    // ItemList_insert(&itemsHead, item4);
    
    // printItemList(itemsHead);
    // ItemList_deleteAtIndex(&itemsHead, 3);
    // printItemList(itemsHead);
    
    // EventNode* events = NULL;
    // EventList_insert(&events, TRAP);
    // EventList_insert(&events, PUZZLE);
    // EventList_insert(&events, BLOCKED);
    // printEventList(events);
    
    // Room* room = Room_construct(0, "Trap", "This is a trap room", NULL, NULL, NULL, NULL, events, itemsHead);
    // Room* room1 = Room_construct(1, "Normal", "This is a normal room", NULL, NULL, NULL, NULL, NULL, NULL, 0);

    // if (room != NULL){
    //     // room->south = room1;
    //     rooms[room->ID] = room;
    //     roomCount ++;
    //     // displayRoom(room);
    // }
    // if (room1 != NULL){
    //     room1->north = room;
    //     rooms[room1->ID] = room1;
    //     roomCount ++;
    //     // displayRoom(room1);
    // }

    // generateLayout(&rooms, &roomCount, 10000, &allocRoomSize);

    // expandRoom(&rooms, room, &roomCount, 10, &allocRoomSize);
    loadLayout(layoutStateFPath, &rooms, &roomCount, &allocRoomSize);
    // displayRooms(rooms, roomCount);
    // saveLayout(layoutStateFPath, rooms, roomCount);

    // savePlayerState(playerStateFPath, player);
    // loadPlayerState(playerStateFPath, player);
   
    // displayRooms(rooms, roomCount);
    
    // int* playerPath = malloc(sizeof(int)*roomCount);
    // int* playerPathCount = 0;
    Player* player = Player_construct("Player", 0, 100, 0, NULL); // We need this store player inventory

    exploreDungeon(rooms[0], player, true);

    // saveLayout(layoutStateFPath, rooms, roomCount);
    // savePlayerState(playerStateFPath, player);

    // int arr[1000];
    // int numberOccurenceProbArr[] = {45, 40, 10, 5};
    // generateRandomIntArrProb(arr, 1000, 0, 3, numberOccurenceProbArr, 4);

    // for (int i=0; i<1000; i++){
    //     printf("\n%d", generateRandomInt(0, 3));
    // }

    freeRooms(&rooms, &roomCount);
    freePlayer(player);
    // freeItemList(&itemsHead);

    return EXIT_SUCCESS;
}
    