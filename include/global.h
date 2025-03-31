#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include <time.h>

#define DNE -1

int generateRandomInt(int start, int end);
int* generateRandomIntArr(int* arr, int arrSize, int start, int end, int filedCount);
int* generateRandomIntArrProb(int* arr, int arrSize, int start, int end, int* numberOccurenceProbArr, int numberOccurenceProbArrCount);

#endif