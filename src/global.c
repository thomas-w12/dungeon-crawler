#include "../include/global.h"
#include <stdio.h>
#include <stdbool.h>


int generateRandomInt(int start, int end){
    return (rand()%((end-start)+1))+start;
}

/// @brief  
/// @param arr Array to prefill with the random values
/// @param start Start number of valid range of values
/// @param end End number of valid range of values
/// @param count Size of the array
/// @param filedCount The number of filled index of the array staring from 0 
/// @return Pointer to the array of values
int* generateRandomIntArr(int* arr, int start, int end, int count, int filedCount){
    if (((end-start+1) < count)){ // +1 since start and end are inclusive
        printf("\nCould not generate %d unique numbers between %d and %d", count, start, end);
        return NULL;
    }
    int validCount = filedCount;
    while (validCount < count){
        int num = generateRandomInt(start, end);

        bool numInArr = false;
        for (int i=0; i<validCount; i++){
            if (arr[i] == num){
                numInArr = true;
            }
        }

        if (numInArr == false){
            arr[validCount] = num;
            validCount ++;
        }
    }
    return arr;
}