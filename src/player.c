#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/room.h"
#include "../include/item.h"
#include "../include/player.h"
#include "../include/npc.h"


Player* Player_construct(char* name, int currentRoom, int health, int score, Room* currentRoomPtr){
    Player* player = (Player*)malloc(sizeof(Player));
    if (player == NULL){
        printf("\nCould not create player");
        return NULL;
    }

    player->name = strdup(name);
    if (player->name == NULL){
        printf("\nCould not create player name");
        free(player);
        return NULL;
    }
    player->currentRoom = currentRoom;
    player->health = health;
    player->score = score;
    
    player->inventory = NULL;
    player->currentRoomPtr = currentRoomPtr;

    return player;
}

void displayPlayer(Player* player){
    printf("\nPlayer - Name: %s\tCurrent Room: %d\tHealth: %d\tScore: %d", player->name, player->currentRoom, player->health, player->score);
    displayPlayerInventory(player);
}

void displayPlayerInventory(Player* player){
    printf("\nItems in inventory (%d): ", itemListCount(player->inventory));
    printItemList(player->inventory);
}

void updatePlayerRoom(Player* player, Room* currentRoom){
    player->currentRoom = currentRoom->ID;
    player->currentRoomPtr = currentRoom;
}

void pickUpItem(Player* player, int pickupItemID){
    if (itemListCount(player->inventory) >= MAX_PLAYER_ITEMS){
        printf("\nInventory is full. Cannot pick up item.");
        return;
    }

    // Find the item with matching ID in the current room
    Item* pickupTargetItem = ItemList_deleteItemID(&player->currentRoomPtr->items, pickupItemID);
    if (pickupTargetItem == NULL) {
        printf("\nInvalid item ID\n");
        return;
    }

    // Add item to player inventory
    ItemList_insert(&player->inventory, pickupTargetItem);
    printf("\nYou picked up an Item. Press i to see your inventory\n");
}

void dropItem(Player* player, int dropItemID){
    if (itemListCount(player->inventory) == 0){
        printf("\nInventory is empty. Cannot drop item.");
        return;
    }

    // Find the item with matching ID in the player's inventory
    Item* dropTargetItem = ItemList_deleteItemID(&player->inventory, dropItemID);

    if (dropTargetItem == NULL) {
        printf("\nInvalid item ID\n");
        return;
    }

    // Add item to room
    ItemList_insert(&player->currentRoomPtr->items, dropTargetItem);
    printf("\nYou dropped an Item. Press i to see your inventory\n");
}

void useItem(Player* player, int itemID){

}

void decreasePlayerHealth(Player* player, int damage){
    player->health -= damage;
    printf("Ouch you took %d %% damage!", damage);
}

void increasePlayerHealth(Player* player, int health){
    player->health += health;
    printf("Your health increased by %d %%", health);
}

void increasePlayerScore(Player* player, int score){
    player->score += score;
}

void freePlayer(Player* player){
    if (player == NULL){
        return;
    }
    free(player->name);
    freeItemList(&player->inventory);
    free(player);
}

void triggerEvent(Room* room, Player* player){
    EventNode* currEventNode = room->events;
    while (currEventNode != NULL){
        Event currEvent = currEventNode->data;
        switch(currEvent){
            case NORMAL:
                printf("\nThis room is a normal room");
                // delete event
                EventList_delete(&room->events, currEvent);
                break;
            case BLOCKED:
                printf("\nThis room is blocked, you need a pick axe to break through");
                int input;
                scanf(" %d", &input);
                break;
            case LOCKED:
                printf("\nThis room is locked, you need a key to open it");
                break;
            case FIRE_TRAP:
                printf("\nYou just got caught in a fire trap! Youre health decreased by 25%%");
                decreasePlayerHealth(player, 25);
                break;
            case PIT_TRAP:
                printf("\nYou just fell into a pit, you dont have a ladder so you died!");
                break;
            case PUZZLE:
                printf("\nYou have to solve this puzzel to coninue to this room");
                break;
            case NPC_BOSS:
            case NPC_TRADE:
            case NPC_TALK:
                NPC npc = createNPC(currEvent);
                npc.interact(&npc, player);
                break;
        }

        currEventNode = currEventNode->next;
    }
}