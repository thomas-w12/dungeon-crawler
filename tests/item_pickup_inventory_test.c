#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/player.h"
#include "../include/room.h"
#include "../include/item.h"

int main() {
    // Create a room with items
    Item* item1 = Item_construct(0); // Sword
    Item* item2 = Item_construct(1); // Shield
    Item* item3 = Item_construct(2); // Ladder
    ItemNode* roomItems = NULL;
    ItemList_insert(&roomItems, item1);
    ItemList_insert(&roomItems, item2);
    ItemList_insert(&roomItems, item3);

    Room* room = Room_construct(0, NULL, NULL, NULL, NULL, NULL, roomItems);
    assert(room != NULL);

    // Create a player
    Player* player = Player_construct("Hero", room->ID, 100, 0, room);
    assert(player != NULL);

    // Test item pickup
    printf("Testing item pickup...\n");
    pickUpItem(player, 0); // Pick up Sword
    assert(itemListCount(player->inventory) == 1); // Inventory should have 1 item
    assert(itemListCount(room->items) == 2); // Room should have 1 item left
    assert(player->inventory->data->ID == 0); // Verify the item in inventory is Sword

    pickUpItem(player, 1); // Pick up Shield
    assert(itemListCount(player->inventory) == 2); // Inventory should have 2 items
    assert(itemListCount(room->items) == 1); // Room should have no items left
    assert(player->inventory->next->data->ID == 1); // Verify the second item in inventory is Shield

    pickUpItem(player, 2); // Attempt to pick up Ladder
    assert(itemListCount(player->inventory) == 3); // Inventory should have 3 items
    assert(itemListCount(room->items) == 0); // Room should still have no items left
    assert(player->inventory->next->next->next == NULL); // Verify there are no more items in inventory

    // Test inventory limit
    printf("Testing inventory limit...\n");
    Item* item4 = Item_construct(3); // potion
    ItemList_insert(&room->items, item4);
    pickUpItem(player, 2); // Attempt to pick up Ladder
    assert(itemListCount(player->inventory) == MAX_PLAYER_ITEMS); // Inventory should still have 2 items
    assert(itemListCount(room->items) == 1); // Room should still have potion

    // Test item drop
    printf("Testing item drop...\n");
    dropItem(player, 0); // Drop Sword
    assert(itemListCount(player->inventory) == 2); // Inventory should have 1 item left
    assert(itemListCount(room->items) == 2); // Room should have 2 items now
    assert(room->items->next->data->ID == 0); // Verify the dropped item is Sword

    // Cleanup
    freePlayer(player);
    freeRooms(&room, &(int){1});

    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}