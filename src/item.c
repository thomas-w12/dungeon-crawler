#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include "../include/room.h"
// #include "../include/player.h"
#include "../include/item.h"


Item* Item_construct(int ID) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    if (!newItem) {
        printf("Error: Could not allocate memory for Item.\n");
        return NULL;
    }
    newItem->ID = ID;
    strcpy(newItem->type, ITEM_TYPES[ID]);
    strcpy(newItem->description, ITEM_DESCRIPTIONS[ID]);
    return newItem;
}


void displayItem(Item* item){
    if (item != NULL) {
        printf("\nItem - ID: %d\tType: %s\tDescription: %s", item->ID, item->type, item->description);
    }
}

void displayItems(Item* items[], int itemCount, int maxItems){
    if (itemCount == 0){
        printf("There are no items!");
        return;
    }

    for (int i=0; i<maxItems; i++){
        displayItem(items[i]);
    }
}

void freeItem(Item* item){
    free(item);
}

void freeItems(Item* items[], int* itemsCount){
    for (int i=0; i<*itemsCount; i++){
        free(items[i]);
    }
    *itemsCount = 0;
}