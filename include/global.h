#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include <time.h>

#define DNE -1

int generateRandomInt(int start, int end);//start and end inclusive
int* generateRandomIntArr(int* arr, int arrSize, int start, int end, int filedCount); //return null if unsuccessfull
int* generateRandomIntArrProb(int* arr, int arrSize, int start, int end, int* numberOccurenceProbArr, int numberOccurenceProbArrCount);
//Maybe add random value generation here
//Generate random array of n unique elements btw start and finish

#endif