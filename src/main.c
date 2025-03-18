#include <stdlib.h>
#include <stdio.h>
#include "../include/fileio.h"
#include "../include/room.h"
#include "../include/player.h"
#include "../include/item.h"


int main() {
    int roomCount = 0;
    Room* rooms[MAX_ROOMS];
    
    char layoutStateFPath[] = {"saved_games/layoutState.txt"};
    // char playerStateFPath[] = {"saved_games/playerState.txt"};

    Item* item1 = Item_construct(0);
    Item* item2 = Item_construct(1);
    Item* item3 = Item_construct(2);
    Item* item4 = Item_construct(3);
    
    Item* itemsArrRoom1[] = {item1, item2, item3, item4}; 
    int itemsLengthRoom1 = sizeof(itemsArrRoom1) / sizeof(Item*);  
    
    Room* room = Room_construct(0, "Trap", "This is a trap room", NULL, NULL, NULL, NULL, itemsArrRoom1, itemsLengthRoom1);
    Room* room1 = Room_construct(1, "Normal", "This is a normal room", NULL, NULL, NULL, NULL, NULL, 0);


    if (room != NULL){
        room->south = room1;
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
    
    saveLayout(layoutStateFPath, rooms, roomCount);
    
    loadLayout(layoutStateFPath, rooms, &roomCount);
   
    displayRooms(rooms, roomCount);
    
    exploreDungeon(room);

    freeRooms(rooms, &roomCount);
    freeItems(itemsArrRoom1, &itemsLengthRoom1);

    return EXIT_SUCCESS;
}
    