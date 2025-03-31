#ifndef NPC_H
#define NPC_H

#include "../include/event.h"
#include "../include/player.h"

#define NPC_RANDOM_CONVO (const char*[]) {"The weather is pretty cold today", "Uhmm, whats your name", "You built a nice project!", "Thank you greg!"}
#define NPC_RANDOM_CONVO_COUNT 4

typedef struct NPC{
    char type[30];
    char dialogue[100];
    int damage;
    void (*interact)(struct NPC* npc, struct Player* player);
} NPC;

NPC createNPC(Event event);
void npcTalk(NPC* npc, Player* player);
void npcAttack(struct NPC* npc, struct Player* player);
void npcTrade(struct NPC* npc, struct Player* player);

#endif