#ifndef ITEM_H
#define ITEM_H

#define ITEM_TYPES (const char*[]){"sword", "stone", "shield", "ladder"}
#define ITEM_DESCRIPTIONS (const char*[]){"Fight off monsters", "Stone the giant", "Shield against trap", "Climb out of trap"}

typedef struct Item{
    // Item type and description depends on the item id
    int ID;
    char type[10];
    char description[20];
} Item;

Item* Item_construct(int ID);
void displayItem(Item* item);
void displayItems(Item* items[], int itemCount);
void freeItem(Item* item);
void freeItems(Item* items[], int* itemsCount);
// void addItemToRoom(Room* room, Item item);
// void addItemToPlayer(Player* player, Item item);
// void removeItemFromRoom(Room* room, Item item); // Remove item after player collects item
// void removeItemFromPlayer(Player* player, Item item); // Remove item after player uses them or dies

#endif