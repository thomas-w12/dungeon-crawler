#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/item.h"
#include "../include/global.h"


Item* Item_construct(int ID) {
    Item* newItem = malloc(sizeof(Item));
    if (!newItem) {
        printf("Error: Could not allocate memory for Item.\n");
        return NULL;
    }
    newItem->ID = ID;
    strcpy(newItem->type, ITEM_TYPES[ID]);
    strcpy(newItem->description, ITEM_DESCRIPTIONS[ID]);
    return newItem;
}

ItemNode* ItemNode_construct(Item* item){
    ItemNode* itemNode = malloc(sizeof(ItemNode));
    if (itemNode == NULL){
        perror("Could not allocate memory for ItemNode");
        return NULL;
    }

    itemNode->data = item;
    itemNode->next = NULL;

    return itemNode;
}

ItemNode* ItemList_insert(ItemNode** head, Item* item){
    ItemNode* itemNode = ItemNode_construct(item);
    if (itemNode == NULL){
        perror("Failed Item List insert");
        return NULL;
    }
    // cannot have duplicate events
    if (*head == NULL){
        *head = itemNode;
    }else{
        ItemNode* curr = *head;

        while(curr->next != NULL){
            if (curr->data->ID == item->ID){
                perror("Duplicate items are not allowed");
                return NULL;
            }
            curr = curr->next;
        }

        curr->next = itemNode;
    }
    return itemNode;
}

Item* ItemList_deleteAtIndex(ItemNode** head, int itemIndex){
    Item* item = NULL;

    if (*head == NULL){
        return item;
    }else if (itemIndex == 0){// remove head
        if ((*head)->next == NULL){
            ItemNode* temp = (*head);
            item = (*head)->data;
            *head = NULL;
            free(temp);
            return item;
        }
        ItemNode* temp = (*head)->next;
        item = (*head)->data;
        free(*head);
        *head = temp;
    }else{
        ItemNode* prev = *head;
        ItemNode* curr = (*head)->next;

        int count = 1; //because we are not staring from the beginnig
        while((curr != NULL) && (itemIndex > count)){
            prev = curr;
            curr = curr->next;
            count++;
        }
        
        if (curr != NULL){
            prev->next = curr->next;
            item = curr->data;
            free(curr);
        }
        displayItem(item);
    }
    return item;
}

Item* ItemList_deleteItemID(ItemNode** head, int itemID){
    Item* item = NULL;

    if (*head == NULL){
        return item;
    }else if (itemID == (*head)->data->ID){// remove head
        if ((*head)->next == NULL){
            ItemNode* temp = (*head);
            item = (*head)->data;
            *head = NULL;
            free(temp);
            return item;
        }
        ItemNode* temp = (*head)->next;
        item = (*head)->data;
        free(*head);
        *head = temp;
    }else{
        ItemNode* prev = *head;
        ItemNode* curr = (*head)->next;

        int count = 1; //because we are not staring from the beginnig
        while((curr != NULL) && (itemID != curr->data->ID)){
            prev = curr;
            curr = curr->next;
            count++;
        }
        
        if (curr != NULL){
            prev->next = curr->next;
            item = curr->data;
            free(curr);
        }
    }
    return item;
}

int itemListCount(ItemNode* head){
    ItemNode* curr = head;
    int count = 0;
    while (curr != NULL){
        curr = curr->next;
        count++;
    }
    return count;
}

void itemListToArr(ItemNode* head, Item* arr[], int arrSize){
    ItemNode* curr = head;
    for (int i=0; i<arrSize; i++){
        if (curr == NULL){
            arr[i] = NULL;
        }else{
            arr[i] = curr->data;
            curr = curr->next;
        }
    }
}

void displayItem(Item* item){
    if (item != NULL) {
        printf("\nItem - ID: %d\tType: %s\tDescription: %s", item->ID, item->type, item->description);
    }else{
        printf("Item is NULL");
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

void printItemList(ItemNode* head){
    if (head == NULL){
        printf("There are no items!");
        return;
    }
    ItemNode* curr = head;
    while (curr != NULL){
        // printf("%d->", curr->data);
        displayItem(curr->data);
        curr = curr->next;
    }
}

void freeItem(Item* item){
    if (item == NULL) {
        return;
    }
    free(item);
}

void freeItemNode(ItemNode* itemNode){
    if (itemNode == NULL) return;
    freeItemNode(itemNode->next);
    free(itemNode->data);
    free(itemNode);
}

void freeItemList(ItemNode** headPtr){
    if (*headPtr == NULL) return;
    freeItemNode(*headPtr);
    *headPtr = NULL;
}

void freeItems(Item* items[], int* itemsCount){
    for (int i=0; i<*itemsCount; i++){
        free(items[i]);
    }
    *itemsCount = 0;
}