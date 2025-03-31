#ifndef ITEM_H
#define ITEM_H

#define ITEM_TYPES (const char*[]){"sword", "shield", "ladder", "potion", "key", "pickaxe"}
#define ITEM_DESCRIPTIONS (const char*[]){"Fight off monsters", "Shield against monsters", "Climb out of trap", "+ 50 health", "Open locked door", "Break blocked room"}
#define TOTAL_ITEMS_COUNT 6 // update this count every time a new item is added to the ITEM_TYPES and ITEM_DESCRIPTIONS

typedef enum ItemsID{
    SWORD,
    SHIELD,
    LADDER,
    POTION,
    KEY,
    PICKAXE,
} ItemsID;


typedef struct Item{
    // Item type and description depends on the item id
    int ID;
    char type[20];
    char description[50];
} Item;

typedef struct ItemNode{
    Item* data;
    struct ItemNode* next;
} ItemNode;

Item* Item_construct(int itemID);
ItemNode* ItemNode_construct(Item* item);
ItemNode* ItemList_insert(ItemNode** head, Item* item);
Item* ItemList_deleteAtIndex(ItemNode** head, int itemIndex);
Item* ItemList_deleteItemID(ItemNode** head, int itemID);
int itemListCount(ItemNode* head);
void itemListToArr(ItemNode* head, Item* arr[], int arrSize);
void freeItemList(ItemNode** head);
void printItemList(ItemNode* head);
void displayItem(Item* item);
void displayItems(Item* items[], int itemCount, int maxItems);
void freeItem(Item* item);
void freeItems(Item* items[], int* itemsCount);

#endif