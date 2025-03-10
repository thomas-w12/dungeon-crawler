#ifndef ROOM_H
#define ROOM_H

typedef struct Room {
    char* name;
    char* description;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
} Room;

#endif