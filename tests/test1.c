#include "../include/item.h"


void test(int** arr){
    arr[0] = malloc(3 * sizeof(int));  // Allocate memory
    arr[0][0] = 1;
    arr[0][1] = 2;
    arr[0][2] = 3;
    printf("%d %d %d", arr[0][1], arr[0][1], arr[0][2]);

    // test(roomConnections);
    // printf("%d %d %d", roomConnections[0][1], roomConnections[0][1], roomConnections[0][2]);
}

void testItem(Item* items[], int itemCount){
    for (int i = 0; i<itemCount; i++){
        displayItem(items[i]);
    }
}

int main(int argc, char *argv[]) {
    printf("test1 executing.\n");
    return 0;
}