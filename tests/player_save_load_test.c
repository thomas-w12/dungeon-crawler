#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/player.h"
#include "../include/fileio.h"
#include "../include/item.h"

int main() {
    srand(time(0));

    // Create items to be added to the room
    Item* item1 = Item_construct(0);
    Item* item2 = Item_construct(1);
    Item* item3 = Item_construct(2);

    ItemNode* itemsHead = NULL;
    ItemList_insert(&itemsHead, item1);
    ItemList_insert(&itemsHead, item2);
    ItemList_insert(&itemsHead, item3);

    // create room
    Room* startingRoom = Room_construct(0, NULL, NULL, NULL, NULL, NULL, itemsHead);
    if (startingRoom == NULL) {
        printf("Error creating starting room.\n");
        return EXIT_FAILURE;
    }

    // Create a player
    Player* player = Player_construct("Hero", startingRoom->ID, 100, 50, startingRoom);

    // Pick up items from the room
    pickUpItem(player, 0); // Pick up item with ID 0
    pickUpItem(player, 1); // Pick up item with ID 1

    // Save player state to a file
    char playerStateFPath[] = "tests/saved_test_games/player_save_load_test_output.txt";
    int saveStatus = savePlayerState(playerStateFPath, player);
    if (saveStatus != EXIT_SUCCESS) {
        printf("Error saving player state to file.\n");
        return EXIT_FAILURE;
    }

    // Load player state from the file
    Player* loadedPlayer = Player_construct("", 0, 0, 0, NULL);
    int loadStatus = loadPlayerState(playerStateFPath, loadedPlayer);
    if (loadStatus != EXIT_SUCCESS) {
        printf("Error loading player state from file.\n");
        return EXIT_FAILURE;
    }

    // Compare the loaded player with the original player
    if (strcmp(player->name, loadedPlayer->name) != 0 ||
        player->currentRoom != loadedPlayer->currentRoom ||
        player->health != loadedPlayer->health ||
        player->score != loadedPlayer->score) {
        printf("Loaded player data does not match saved player data.\n");
        return EXIT_FAILURE;
    }

    // Compare the inventory
    ItemNode* originalItem = player->inventory;
    ItemNode* loadedItem = loadedPlayer->inventory;
    while (originalItem != NULL && loadedItem != NULL) {
        if (originalItem->data->ID != loadedItem->data->ID) {
            printf("Loaded inventory item does not match saved inventory item.\n");
            return EXIT_FAILURE;
        }
        originalItem = originalItem->next;
        loadedItem = loadedItem->next;
    }
    if (originalItem != NULL || loadedItem != NULL) {
        printf("Loaded inventory size does not match saved inventory size.\n");
        return EXIT_FAILURE;
    }

    printf("Player data matches between saved and loaded player.\n");

    // Compare the saved file with the expected file
    char expectedPlayerStateFPath[] = "tests/saved_test_games/player_save_load_test_expected.txt";
    FILE* savedFile = fopen(playerStateFPath, "r");
    FILE* expectedFile = fopen(expectedPlayerStateFPath, "r");

    if (savedFile == NULL || expectedFile == NULL) {
        printf("Error opening saved or expected file for comparison.\n");
        return EXIT_FAILURE;
    }

    char savedLine[256];
    char expectedLine[256];
    int lineNumber = 1;
    while (fgets(savedLine, sizeof(savedLine), savedFile) && fgets(expectedLine, sizeof(expectedLine), expectedFile)) {
        if (strcmp(savedLine, expectedLine) != 0) {
            printf("Mismatch at line %d:\n", lineNumber);
            printf("Saved:    %s", savedLine);
            printf("Expected: %s", expectedLine);
            fclose(savedFile);
            fclose(expectedFile);
            return EXIT_FAILURE;
        }
        lineNumber++;
    }

    fclose(savedFile);
    fclose(expectedFile);

    printf("Saved player file matches expected player file.\n");

    // Free memory
    freePlayer(player);
    freePlayer(loadedPlayer);
    free(startingRoom);

    printf("Test passed!\n");
    return EXIT_SUCCESS;
}