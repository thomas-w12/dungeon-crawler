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
        printf("Could not generate %d unique numbers between %d and %d\n", arrSize, start, end);
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

/// @brief Fill an array with random numbers based on probability
/// @param arr Array to fill with random values
/// @param arrSize Size of arr
/// @param start Start number of valid range of values
/// @param end End number of valid range of values
/// @param numberOccurenceProbArr Array that contains the probability in % of occurence of a random number between start and end
/// @param numberOccurenceProbArrCount Size of numberOccurenceProbArr 
/// @return The pointer to arr
int* generateRandomIntArrProb(int* arr, int arrSize, int start, int end, int* numberOccurenceProbArr, int numberOccurenceProbArrCount){
    int probSum = 0;
    for (int i=0; i<numberOccurenceProbArrCount; i++){
        probSum += numberOccurenceProbArr[i];
    }
    if (probSum < 100) {
        printf("The sum of the probability arr has to be at least 100%%\n");
        return NULL;
     }

    int* numberOccurenceArr = calloc(numberOccurenceProbArrCount, sizeof(int));

    if (numberOccurenceArr == NULL){
        perror("Could not allocate memory for numberOccurenceArr\n");
        return NULL;
    }

    for (int i=0; i<arrSize; i++){
        while (true){
            int randNum = generateRandomInt(start, end);
            int randNumIndex = randNum-start; // since it's an interval shift to the left by start num (is start is 2, index of randNum=2 is 2-2=0 )
            float interval = 1.0/(numberOccurenceProbArr[randNumIndex]/100.0);
            int randNumCount = numberOccurenceArr[randNumIndex];
            if (i >= (randNumCount*interval)){
                arr[i] = randNum;
                numberOccurenceArr[randNumIndex] ++;
                break;
            }
        }
    }
    
    free(numberOccurenceArr);
    return arr;
}
