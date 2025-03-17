#include <stdlib.h>
#include <stdio.h>
#include "../include/fileio.h"
#include "../include/room.h"
#include "../include/player.h"
#include "../include/item.h"

void test(int** arr){
    arr[0] = malloc(3 * sizeof(int));  // Allocate memory
    arr[0][0] = 1;
    arr[0][1] = 2;
    arr[0][2] = 3;
    printf("%d %d %d", arr[0][1], arr[0][1], arr[0][2]);

    // test(roomConnections);
    // printf("%d %d %d", roomConnections[0][1], roomConnections[0][1], roomConnections[0][2]);
}

void testItem(Item items[], int itemCount){
    for (int i = 0; i<itemCount; i++){
        displayItem(items[i]);
    }
}

#include "../include/game_loop.h"

int main(int argc, char *argv[]) {
    int roomCount = 0;
    Room* rooms[MAX_ROOMS];
    Player player;
    
    char layoutStateFPath[] = {"saved_games/layoutState.txt"};
    char playerStateFPath[] = {"saved_games/playerState.txt"};

    Item* item1 = Item_construct(0);
    Item* item2 = Item_construct(1);
    Item* item3 = Item_construct(2);
    Item* item4 = Item_construct(3);
    
    Item itemsArr[] = {*item1, *item2, *item3, *item4}; 
    int itemsLength = sizeof(itemsArr) / sizeof(Item);  
    

    Room* room = Room_construct(0, "Trap", "This is a trap room", NULL, NULL, NULL, NULL, itemsArr, itemsLength);
    Room* room1 = Room_construct(1, "Normal", "This is a normal room", NULL, NULL, NULL, NULL, itemsArr, 0);


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
    // exploreDungeon(room);
    loadLayout(layoutStateFPath, rooms, &roomCount);
    // printf("\n%d", roomCount);
   
    // printf("\n%d", roomCount);
    displayRooms(rooms, roomCount);
    // printf("\n%d", roomCount);
    
    // Room_destroy(room);
    freeRooms(rooms, &roomCount);

    game_loop();

    free(item1);
    free(item2);
    free(item3);
    free(item4);

    return EXIT_SUCCESS;
}
    