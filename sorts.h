#include <iostream>
#include <cstring>
using namespace std;

#ifndef SORTS_H
#define SORTS_H
void mergeSort(int* ar, int size);//1
void insertionSort(int* ar,int  size);//2
void bubbleSort(int* ar,int size);//3
void selectionSort(int* ar, int size);//4
void countsort(int *ar, int size);//5
void quickSort(int* ar, int size);//6
void sorts(void (*sortName)(int*, int), int* ar, int size);

#endif
