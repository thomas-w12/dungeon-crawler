#ifndef NPC_H
#define NPC_H

#include "../include/event.h"
#include "../include/player.h"

#define NPC_RANDOM_CONVO (const char*[]) {"I lost my sword in the caves below. If you find it, perhaps fate will favor you.", "I saw a ghost in the next room. She told me a riddle, but I forgot the answer…", "A challenge for you! - Solve this riddle: What has hands but cannot clap? (Waits for answer: 'Clock')", "A friendly tip! - If you see a black cat in this dungeon... follow it. It might lead you somewhere interesting!", "Did you know? - Bats always turn left when exiting a cave.", "A little wisdom for you. - An octopus has three hearts. Imagine the heartbreak!"}
#define NPC_RANDOM_CONVO_COUNT 6

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