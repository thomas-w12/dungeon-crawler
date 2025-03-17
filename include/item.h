#ifndef ITEM_H
#define ITEM_H


// #define ITEM_0 "sword"
// #define ITEM_1 "ladder"
// #define ITEM_2 "shield"
// #define ITEM_0_DESCRIPTION "Fight off monsters"
// #define ITEM_1_DESCRIPTION "Climb out of trap"
// #define ITEM_2_DESCRIPTION "Shield agains trap" // For this if a new item is added it would have to updated everywhere

#define ITEM_TYPES (const char*[]){"sword", "stone", "shield", "ladder"}
#define ITEM_DESCRIPTIONS (const char*[]){"Fight off monsters", "Stone the giant", "Shield agains trap", "Climb out of trap"}

typedef struct Item{
    // Item type and description depends on the item id
    int ID;
    char type[10];
    char description[20];
} Item;

Item* Item_construct(int ID);
void displayItem(Item item);
void displayItems(Item items[], int itemCount);
// void addItemToRoom(Room* room, Item item);
// void addItemToPlayer(Player* player, Item item);
// void removeItemFromRoom(Room* room, Item item); // Remove item after player collects item
// void removeItemFromPlayer(Player* player, Item item); // Remove item after player uses them or dies

#endif