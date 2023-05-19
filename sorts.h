#include <iostream>
#include <cstring>
#include "sqlite3.h"



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

class DataBase{
    private:	
        void CreateSortsTable();
        void CreateTimeSortsTable();
        void CreateResSortsTable();
	sqlite3 *bd;
    public:
        DataBase();
        DataBase(const char* bd_name);
	~DataBase();
        bool openBd(const char* bdName);
        bool closeBd();
        bool request_insert_create(const char* sqlString);
        bool request_select(const char* sqlString, int (*callback)(void*,int,char**,char**), void* outS);
        static int callbackId(void* outputStruct, int countRec, char** argv, char** colName);
        bool SelectidFromArsize(int arsize, int &id);
};
void checkkeys(int argc, char **argv, int* flags,int& maxsize, int& step);
#endif
