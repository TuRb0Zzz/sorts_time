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
/* problems......
class DataBase{
    private:
        void CreateSortsTable();
        void CreateTimeSortsTable();
        void CreateResSortsTable();
    public:
        DataBase();
        ~DataBase();
        bool openBd(const char* bdName);
        bool closeBd();
        bool request_insert_create(const char* sqlString);
        bool request_select(const char* sqlString);
        static int callback(void* outputStruct, int countRec, char** argv, char** colName);
};
*/
#endif
