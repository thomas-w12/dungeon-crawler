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
    
    
    EventNode* events = NULL;
    EventList_insert(&events, FIRE_TRAP);
    
    Room* room = Room_construct(0, NULL, NULL, NULL, NULL, events, NULL);
    Room* room1 = Room_construct(1, NULL, NULL, NULL, NULL, NULL, NULL);

    if (room != NULL){
        // room->south = room1;
        rooms[room->ID] = room;
        roomCount ++;
        // displayRoom(room);
    }
    if (room1 != NULL){
        room1->north = room;
        rooms[room1->ID] = room1;
        roomCount ++;
        // displayRoom(room1);
    }


    int* playerPath = malloc(sizeof(int)*roomCount);
    int allocPathSize = 0;
    int playerPathCount = 0;
    Player* player = Player_construct("Player", 0, 100, 0, NULL); // We need this store player inventory

    // exploreDungeon(NULL, rooms[0], player, &playerPath, &allocPathSize, &playerPathCount);

    

    freeRooms(&rooms, &roomCount);

    return EXIT_SUCCESS;
}
    