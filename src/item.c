#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include "../include/room.h"
// #include "../include/player.h"
#include "../include/item.h"


Item Item_construct(int ID){
    Item item;
    item.ID = ID;
    
    strcpy(item.type, ITEM_TYPES[ID]);
    strcpy(item.description, ITEM_DESCRIPTIONS[ID]);

    return item;
}

void displayItem(Item item){
    printf("\nItem - ID: %d\tType: %s\tDescription: %s", item.ID, item.type, item.description);
}

void displayItems(Item items[], int itemCount){
    if (itemCount == 0){
        printf("There are no items!");
        return;
    }

    for (int i=0; i<itemCount;i++){
        displayItem(items[i]);
    }
}
