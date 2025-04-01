#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/event.h"
#include "../include/npc.h"
#include "../include/player.h"
#include "../include/global.h"


NPC createNPC(Event event){
    NPC npc;
    switch(event){
        case NPC_BOSS:
            strcpy(npc.type, "NPC BOSS");
            strcpy(npc.dialogue, "You have met a boss! Prepare to die");
            npc.damage = 100;
            npc.interact = npcAttack;
            break;
        case NPC_TALK:
            strcpy(npc.type, "NPC Yapper");
            strcpy(npc.dialogue, "Hi i have a random fact for you today. Would you like to hear it");
            npc.damage = 0;
            npc.interact = npcTalk;
            break;
        case NPC_TRADE:
            strcpy(npc.type, "NPC Trader");
            strcpy(npc.dialogue, "I can trade you 1 item you really need for 2 times you have");
            npc.damage = 0;
            npc.interact = npcTrade;
            break;
        default:
            strcpy(npc.type, "NPC Yapper");
            strcpy(npc.dialogue, "Hi i have a random fact for you today. Would you like to hear it");
            npc.damage = 0;
            npc.interact = npcTalk;
            break;
    }
    return npc;
}

void npcAttack(NPC* npc, Player* player){
    printf("%s\n", npc->dialogue);

    int damage = npc->damage;
    Item* sword = ItemList_deleteItemID(&player->inventory, (int) SWORD); // Find and remove from player inventory
    if (sword != NULL){
        // if player has sword reduce damage by 30%
        printf("You used your sword to deal some damage!\n");
        damage -= (int) (damage*0.3);
    }
    Item* shield = ItemList_deleteItemID(&player->inventory, (int) SHIELD);
    if (shield != NULL){
        // if player has shield reduce damage by 30%
        printf("You used your shield to defend against some damage!\n");
        damage -= (int) (damage*0.3);
    }

    // apply damage to player
    decreasePlayerHealth(player, damage);
}

void npcTalk(NPC* npc, Player* player){
    printf("%s\n", npc->dialogue);
    printf("Press: \nA - hear him out\nX - not interested\n");

    bool correctCommand = false;
    while (! correctCommand){
        char choice = getUserInputCommand();
        switch(choice){
            case ACCEPT: {
                int convoIndex = generateRandomInt(0, NPC_RANDOM_CONVO_COUNT-1);
                printf("%s\n", NPC_RANDOM_CONVO[convoIndex]);
                correctCommand = true;
                break;
            }
            case DECLINE:
                printf("Understandable have a nice day!\n");
                correctCommand = true;
                break;
            default:
                printf("Invalid command\n");
                printf("Press: \nA - hear him out\nX - not interested\n");
                break;
        }
    }
}

bool validateItemTradeIn(Player* player, char message[]){
    printf("%s", message);

    int item = parse_item_command();

    if (item == -1){
        printf("Understandable have a nice day!\n");
        return false;
    }else{
        if (ItemList_deleteItemID(&player->inventory, item) == NULL){
            printf("Invalid itemId\nPress -1 to quit\n");
            printf("Your inventory: ");
            printItemList(player->inventory);
            return validateItemTradeIn(player, message);
        }else{
            return true;
        }
    }
}

bool validateItemTradeOut(Player* player, char message[]){
    printf("%s", message);

    int item = parse_item_command();

    if (item == -1){
        printf("Understandable have a nice day!\n");
        return false;
    }else{
        if (item > TOTAL_ITEMS_COUNT-1){
            printf("Invalid itemId\nPress -1 to quit\n");
            
            return validateItemTradeOut(player, message);
        }else{
            ItemList_insert(&player->inventory, Item_construct(item));
            return true;
        }
    }
}

void npcTrade(NPC* npc, Player* player){
    printf("%s\n", npc->dialogue);
    printf("Press: \nA - trade 2 items\nX - not interested\n");
    char choice = getUserInputCommand();

    bool correctCommand = false;
    while (! correctCommand){
        switch(choice){
            case ACCEPT:
                displayPlayer(player);
                if (itemListCount(player->inventory) < 2){
                    printf("You do not have enough items to trade!\n");
                }else{
                    if (! validateItemTradeIn(player, "Enter the id of the first item to trade: ")){
                        correctCommand = true;
                        break;
                    }

                    if (! validateItemTradeIn(player, "Enter the id of the second item to trade: ")){
                        correctCommand = true;
                        break;
                    }

                    char message[200];
                    int msgLen = 0;

                    msgLen += sprintf(message + msgLen, "Enter the id of the item you want\nItem - ItemID\n");
                    for (int i=0; i<TOTAL_ITEMS_COUNT; i++){
                        msgLen += sprintf(message + msgLen, "%s - %d\n", ITEM_TYPES[i], i);
                    }
                    
                    if (! validateItemTradeOut(player, message)){
                        correctCommand = true;
                        break;
                    }
                    printf("Trade was successfull. Use command i to check your inventory\n");
                }
                correctCommand = true;
                break;
            case DECLINE:
                printf("Understandable have a nice day!\n");
                correctCommand = true;
                break;
            default:
                printf("Invalid command\n");
                printf("Press: \nA - hear him out\nX - not interested\n");
        }
    }
}