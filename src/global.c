#include "../include/global.h"
#include <stdio.h>
#include <stdbool.h>

/// @brief Generate a random int between start and end inclusive
/// @param start 
/// @param end 
/// @return Randomly generated integer value
int generateRandomInt(int start, int end){
    return (rand()%((end-start)+1))+start;
}

/// @brief  
/// @param arr Array to prefill with the random values
/// @param arrSize Size of the array
/// @param start Start number of valid range of values
/// @param end End number of valid range of values
/// @param filledCount The number of filled index of the array staring from 0 
/// @return Pointer to the array of values
int* generateRandomIntArr(int* arr,  int arrSize,int start, int end, int filledCount){
    if (((end-start+1) < arrSize)){ // +1 since start and end are inclusive
        printf("\nCould not generate %d unique numbers between %d and %d", arrSize, start, end);
        return NULL;
    }
    int validCount = filledCount;
    while (validCount < arrSize){
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

// Fill an array with random numbers based on probability
int* generateRandomIntArrProb(int* arr, int arrSize, int start, int end, int* numberOccurenceProbArr, int numberOccurenceProbArrCount){
    // if (start != 0) return NULL; // might have to remove this since we are gewtting the randIndex from the for loop

    int probSum = 0;
    for (int i=0; i<numberOccurenceProbArrCount; i++){
        probSum += numberOccurenceProbArr[i];
    }
    if (probSum < 100) {
        printf("\nThe sum of the probability arr has to be at least 100%%");
        return NULL;
     } // Because might cause an inifinite loop;

    int* numberOccurenceArr = calloc(numberOccurenceProbArrCount, sizeof(int));

    if (numberOccurenceArr == NULL){
        perror("\nCould not allocate memory for numberOccurenceArr");
        return NULL;
    }

    for (int i=0; i<arrSize; i++){
        while (true){
            int randNum = generateRandomInt(start, end);
            int randNumIndex = randNum-start; // since it's an interval shift to the left by start num (is start is 2, index of randNum=2 is 2-2=0 )
            float interval = 1.0/(numberOccurenceProbArr[randNumIndex]/100.0);
            int randNumCount = numberOccurenceArr[randNumIndex];
            // printf("\nInterval: %f, Rand num: %d, Occurence: %d, Prob: %f", interval, randNum, numberOccurenceArr[randNumIndex], (numberOccurenceProbArr[randNumIndex]/100.0));
            if (i >= (randNumCount*interval)){
                arr[i] = randNum;
                numberOccurenceArr[randNumIndex] ++;
                break;
            }
        }
    }
    
    // printf("\nNumberOccurenceProbArrCount: \n");
    // for (int i=0; i<numberOccurenceProbArrCount; i++){
    //     printf("index: %d, val: %d\n", i, numberOccurenceProbArr[i]);
    // }

    // printf("\nNumberOccurenceArr: \n");
    // for (int i=0; i<numberOccurenceProbArrCount; i++){
    //     printf("index: %d, val: %d\n", i, numberOccurenceArr[i]);
    // }

    // printf("\nArr: \n");
    // for (int i=0; i<arrSize; i++){
    //     printf("index: %d, val: %d\n", i, arr[i]);
    // }

    free(numberOccurenceArr);
    return arr;
}
