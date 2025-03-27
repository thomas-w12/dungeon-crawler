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


int main() {
    srand(time(0));

    int allocRoomSize = 10; // initial rooms alloc size
    int roomCount = 0;
    Room** rooms = malloc(sizeof(Room*) * allocRoomSize);
    if (rooms == NULL){
        perror("Could not allocate memory for rooms");
        return EXIT_FAILURE;
    }
    // Room** rooms = malloc(sizeof(Room*)*MAX_ROOMS); // should be * initial rooms alloc size
    
    char layoutStateFPath[] = {"saved_games/layoutState.txt"};
    char playerStateFPath[] = {"saved_games/playerState.txt"};

    Item* item1 = Item_construct(0);
    Item* item2 = Item_construct(1);
    Item* item3 = Item_construct(2);
    Item* item4 = Item_construct(3);
    
    Item* itemsArrRoom1[] = {item1, item2, item3, item4}; 
    int itemsLengthRoom1 = sizeof(itemsArrRoom1) / sizeof(Item*);  

    EventNode* events = EventNode_construct(TRAP);
    
    // Room* room = Room_construct(0, "Trap", "This is a trap room", events, NULL, NULL, NULL, NULL, itemsArrRoom1, itemsLengthRoom1);
    // Room* room1 = Room_construct(1, "Normal", "This is a normal room", NULL, NULL, NULL, NULL, NULL, NULL, 0);

    Player* player = Player_construct("Player", 0, 100, 0, NULL);


    // if (room != NULL){
    //     room->south = room1;
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
    generateLayout(&rooms, &roomCount, 10, &allocRoomSize);
    displayRooms(rooms, roomCount);
    // saveLayout(layoutStateFPath, rooms, roomCount);
    // loadLayout(layoutStateFPath, rooms, &roomCount);

    // savePlayerState(playerStateFPath, player);
    // loadPlayerState(playerStateFPath, player);
   
    // displayRooms(rooms, roomCount);
    
    exploreDungeon(rooms[0], player, true);

    // saveLayout(layoutStateFPath, rooms, roomCount);
    // savePlayerState(playerStateFPath, player);

    freeRooms(rooms, &roomCount);
    freeItems(itemsArrRoom1, &itemsLengthRoom1);

    return EXIT_SUCCESS;
}
    