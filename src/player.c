#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/room.h"
#include "../include/item.h"
#include "../include/player.h"
#include "../include/npc.h"
#include "../include/global.h"


Player* Player_construct(char* name, int currentRoom, int health, int score, Room* currentRoomPtr){
    Player* player = (Player*)malloc(sizeof(Player));
    if (player == NULL){
        printf("Could not create player\n");
        return NULL;
    }

    player->name = strdup(name);
    if (player->name == NULL){
        printf("Could not create player name\n");
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
    printf("Player - Name: %s\tCurrent Room: %d\tHealth: %d\tScore: %d\n", player->name, player->currentRoom, player->health, player->score);
    displayPlayerInventory(player);
}

void displayPlayerInventory(Player* player){
    printf("Items in inventory (%d): \n", itemListCount(player->inventory));
    printItemList(player->inventory);
}

void updatePlayerRoom(Player* player, Room* currentRoom){
    player->currentRoom = currentRoom->ID;
    player->currentRoomPtr = currentRoom;
}

void pickUpItem(Player* player, int pickupItemID){
    if (itemListCount(player->inventory) >= MAX_PLAYER_ITEMS){
        printf("Inventory is full. Cannot pick up item.\n");
        return;
    }

    // Find the item with matching ID in the current room
    Item* pickupTargetItem = ItemList_deleteItemID(&player->currentRoomPtr->items, pickupItemID);
    if (pickupTargetItem == NULL) {
        printf("Invalid item ID\n");
        return;
    }

    // Add item to player inventory
    ItemList_insert(&player->inventory, pickupTargetItem);
    printf("You picked up an Item. Press i to see your inventory\n");
}

void dropItem(Player* player, int dropItemID){
    if (itemListCount(player->inventory) == 0){ // Redundant, should remove
        printf("Inventory is empty. Cannot drop item.\n");
        return;
    }

    // Find the item with matching ID in the player's inventory
    Item* dropTargetItem = ItemList_deleteItemID(&player->inventory, dropItemID);

    if (dropTargetItem == NULL) {
        printf("Invalid item ID\n");
        return;
    }

    // Add item to room
    ItemList_insert(&player->currentRoomPtr->items, dropTargetItem);
    printf("You dropped an Item. Press i to see your inventory\n");
}

bool useItem(Player* player, int itemID){
    if (itemListCount(player->inventory) == 0){ // Redundant, should remove
        printf("Inventory is empty. There is no item to use.\n");
        return false;
    }
    
    bool usedItem = false;

    switch((ItemsID) itemID){
        case POTION:
            if (ItemList_deleteItemID(&player->inventory, itemID) == NULL){
                printf("You don't have any %s.\n", ITEM_TYPES[(int) POTION]);
            }else{
                increasePlayerHealth(player, 50);
                usedItem = true;
            }
            break;
        default:
            printf("You can not use this item\n");
            break;
    }
    return usedItem;
}

void decreasePlayerHealth(Player* player, int damage){
    player->health -= damage;
    printf("Ouch you took %d%% damage!\n", damage);
}

void increasePlayerHealth(Player* player, int health){
    player->health = (player->health + health) > 100 ? 100 : player->health + health;
    printf("Your health increased by %d%%\n", health);
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

bool validateItemUse(Player* player, char message[], ItemsID validItemId){
    printf("%s", message);

    int item = parse_item_command();

    if (item == -1){
        printf("Understandable have a nice day!\n");
        return false;
    }else{
        if (item != (int) validItemId){
            printf("Wrong item!\nYou need a %s - %d\n", ITEM_TYPES[(int) validItemId], (int) validItemId);
            return validateItemUse(player, message, validItemId);
        }else if (ItemList_deleteItemID(&player->inventory, item) == NULL){
            printf("You dont have that item\nPress -1 to quit\n");
            printf("Your inventory(%d): \n", itemListCount(player->inventory));
            printItemList(player->inventory);
            return validateItemUse(player, message, validItemId);
        }else{
            return true;
        }
    }
}

bool triggerBlockedEvent(Room* room, Player* player){
    char choice = getUserInputCommand();
    switch(choice){
        case USE:
            if (validateItemUse(player, "Enter the id of the item you would like to use: ", PICKAXE) == false) return false;

            printf("You just broke throught the room, you can now enter it.\n");
            return true;
        case DECLINE:
            printf("Alright, room ignored\n");
            return false;
        default:
            printf("Invalid choice\nPress:\nU - use an item\nX - Ignore room\n");
            return triggerBlockedEvent(room, player);
    }
}

bool triggerLockedEvent(Room* room, Player* player){
    char choice = getUserInputCommand();
    switch(choice){
        case USE:
            if (validateItemUse(player, "Enter the id of the item you would like to use: ", KEY) == false) return false;

            printf("You just unlocked the room, you can now enter it.\n");
            return true;
        case DECLINE:
            printf("Alright, room ignored\n");
            return false;
        default:
            printf("Invalid choice\nPress:\nU - use an item\nX - Ignore room\n");
            return triggerLockedEvent(room, player);
    }
}

bool triggerPitTrapEvent(Player* player){
    if (ItemList_deleteItemID(&player->inventory, LADDER) != NULL){
        printf("\nYou just fell into a pit, but you climbed out of it with your ladder!\n");
    }else{
        printf("\nYou just fell into a pit.\n");
        decreasePlayerHealth(player, 100);
    }
    return true;
}

bool triggerPuzzleEvent(Room* room, Player* player, int puzzleIndex){
    char userAnswerBuff[100];
    scanf(" %99[^\n]", userAnswerBuff);
    clearBuffer();
    
    if (toupper((int)userAnswerBuff[0]) == (int) DECLINE){
        return false;
    }

    if (strcmp(userAnswerBuff, PUZZLE_ANSWERS[puzzleIndex]) == 0){
        printf("Correct answer, you can proceed to the room\n");
        return true;
    }else{
        printf("Wrong answer! \nTry again! or Enter 'X' to quit\n" );
        return triggerPuzzleEvent(room, player, puzzleIndex);
    }
}

bool triggerEvents(Room* room, Player* player){
    bool eventsPassed = true;
    
    EventNode* currEventNode = room->events;

    while (currEventNode != NULL){
        Event currEvent = currEventNode->data;
        eventsPassed &= triggerEvent(room, player, currEvent);

        if (eventsPassed == false) return eventsPassed; // Dont continue if one event fails
        if (player->health <= 0) return false;

        currEventNode = currEventNode->next;
    }

    printf("Events Passed: %d\n", eventsPassed);
    return eventsPassed;
}

bool triggerEvent(Room* room, Player* player, Event currEvent){
    bool eventPassed = false;
    switch(currEvent){
        case NORMAL:
            printf("This room is a normal room\n");
            EventList_delete(&room->events, currEvent);
            eventPassed = true;
            break;
        case BLOCKED:
            printf("This room is blocked, you need a pick axe to break through\nPress:\nU - use an item\nX - Ignore room\n");
            eventPassed = triggerBlockedEvent(room, player);
            if (eventPassed) EventList_delete(&room->events, currEvent);
            break;
        case LOCKED:
            printf("This room is locked, you need a key to open it\nPress:\nU - use an item\nX - Ignore room\n");
            eventPassed = triggerLockedEvent(room, player);
            if (eventPassed) EventList_delete(&room->events, currEvent);
            break;
        case FIRE_TRAP:
            printf("You just got caught in a fire trap!\n");
            decreasePlayerHealth(player, 25);
            eventPassed = true;
            break;
        case PIT_TRAP:
            eventPassed = triggerPitTrapEvent(player);
            break;
        case PUZZLE:
            printf("You have to solve this puzzle to continue to this room\n");
            int puzzleIndex = generateRandomInt(0, PUZZLE_COUNT-1);
            printf("%s\n", PUZZLE_QUESTIONS[puzzleIndex]);
            eventPassed = triggerPuzzleEvent(room, player, puzzleIndex);
            if (eventPassed) EventList_delete(&room->events, currEvent);
            break;
        case NPC_BOSS:
            break;
        case NPC_TRADE:
        case NPC_TALK:
            NPC npc = createNPC(currEvent);
            npc.interact(&npc, player);
            eventPassed = true;

            if (currEvent == NPC_BOSS) EventList_delete(&room->events, currEvent);
            break;
        case POISON_TRAP:
            printf("You just entered a poison room!\n");
            decreasePlayerHealth(player, 15);
            eventPassed = true;
            break;
    }

    return eventPassed;
}