#ifndef ITEM_H
#define ITEM_H

#define ITEM_TYPES (const char*[]){"sword", "stone", "shield", "ladder", "potion", "key"}
#define ITEM_DESCRIPTIONS (const char*[]){"Fight off monsters", "Stone the giant", "Shield against trap", "Climb out of trap", "+ 50 health", "open locked door"}

typedef struct Item{
    // Item type and description depends on the item id
    int ID;
    char type[10];
    char description[20];
} Item;

typedef struct ItemNode{
    Item* data;
    struct ItemNode* next;
} ItemNode;

Item* Item_construct(int ID);
void displayItem(Item* item);
void displayItems(Item* items[], int itemCount, int maxItems);
void freeItem(Item* item);
void freeItems(Item* items[], int* itemsCount);
// void addItemToRoom(Room* room, Item item);
// void addItemToPlayer(Player* player, Item item);
// void removeItemFromRoom(Room* room, Item item); // Remove item after player collects item
// void removeItemFromPlayer(Player* player, Item item); // Remove item after player uses them or dies

#endif