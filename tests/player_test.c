#include <stdlib.h>
#include <stdio.h>
#include "../include/item.h"
#include "../include/room.h"
#include "../include/player.h"
#include "../include/fileio.h"

int main(int argc, char *argv[]) {
    
    int roomCount = 0;
    Room* rooms[MAX_ROOMS];
    
    char layoutStateFPath[] = {"tests/saved_test_games/layoutState.txt"};
    char playerStateFPath[] = {"tests/saved_test_games/playerState.txt"};

    Item* item1 = Item_construct(0);
    Item* item2 = Item_construct(1);
    Item* item3 = Item_construct(2);
    Item* item4 = Item_construct(3);
    
    Item* itemsArrRoom1[] = {item1, item2, item3, item4}; 
    int itemsLengthRoom1 = sizeof(itemsArrRoom1) / sizeof(Item*);  
    
    Room* room = Room_construct(0, "Trap", "This is a trap room", NULL, NULL, NULL, NULL, itemsArrRoom1, itemsLengthRoom1);
    rooms[roomCount] = room;
    roomCount++;

    Player* player = Player_construct("Player1", 0, 100, 0);
    displayPlayer(player);
    pickUpItem(player, item1);
    pickUpItem(player, item2);

    saveLayout(layoutStateFPath, rooms, roomCount);
    savePlayerState(playerStateFPath, player);

    //freePlayer(player);
    // freeItems(itemsArrRoom1, &itemsLengthRoom1);
    // freeRooms(rooms, &roomCount);
}