#include <iostream>
#include "arraywork.h"
#include "sorts.h"
#include "sqlite3.h"
using namespace std;

void insertionSort(int* ar,int size){
        int element;
        int indexArr;
        int j;
        int key=0;
        for(int i = 1; i < size; i++) {//i- текущий элемент
        

                key=0;
                for( j = i-1; j >= 0; j--) { //j- по какой элемент с i мы будим двигать
                       
                        if (ar[j] > ar[i]) {
                                key=1;
                                element = ar[i];//запомнили элемнт который мы будем двигать
                                indexArr = j+1; //запомнили по какой индекс с конца по начало будем двигаться 
                                break;
                        }
                }
                if(key==0){
                     element = ar[i];
                     indexArr = j+1;
                }
                for(  j= i-1; j>=indexArr; j--){
                      
                        ar[ j+1] = ar[ j];
                }//переставили элементы
                ar[indexArr] = element;//в ручную бахнули элемент с конца по начало 
        }
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
void quickSort(int* ar, int size) {
	int left = 0;
	int right = size - 1;
	int pivot = ar[size >> 1];

	while(left <= right) {
		while(ar[left] < pivot) {
			left++;
		}

		while (ar[right] > pivot) {
			right--;
		}

		if (left <= right) {
			swap(ar[right], ar[left]);
			right--;
			left++;
		}
	}
	if (right > 0) {
		quickSort(&ar[0], right + 1);
	}

	if (left < size) {
		quickSort(&ar[left], size - left);
	}
}
static void merge(int* ar, int size, int central) {
    int left = 0;
    int right = central;
    int* arTemp = new int [size];
    int indexTemp = 0;

    while (left < central && right < size) {
        while(ar[left] <= ar[right] && left < central) {
            arTemp[indexTemp++] = ar[left++];
        }
        while(ar[left] > ar[right] && right < size) {
            arTemp[indexTemp++] = ar[right++];
        }
    }

    while (left < central) {
        arTemp[indexTemp++] = ar[left++];
    }
    while (right < size) {
        arTemp[indexTemp++] = ar[right++];
    }

    memcpy(ar, arTemp, size * sizeof(int));

    delete [] arTemp;
}

void mergeSort(int* ar, int size) {
    if (size <= 1) {
        return;
    }
    mergeSort(&ar[0], size >> 1);
    mergeSort(&ar[size >> 1], size - (size >> 1));

    merge(ar, size, size >> 1);
}

void bubbleSort(int* ar,int size){
    int num;
    for(int s=size;s>0;s--){
        for(int i=0;i<size-1;i++){
            if (ar[i]<ar[i+1]){
                num = ar[i];
                ar[i]=ar[i+1];
                ar[i+1]=num;
            }
        }
    }
}
void selectionSort(int* ar,int size){
    int tmpMax;
    int nb;
    int tmp;
    int bufer;
     for(int i=0;i<size;i++){
         tmpMax=ar[i];//предпологаем что 1 элемент последовательности максимальный
        nb=i;//запоминаем индекс начала проверяемого массива
       tmp=i;//для индекса максимума
       for (int j=i+1;j<size;j++){
          if(tmpMax>ar[j]){
              tmpMax=ar[j];//нашли локальный максимум
              tmp=j;//сохранили индекс максимума
          }
       }
         
       bufer=ar[nb];//меняем местами макс и начало
        ar[nb]=ar[tmp];
        ar[tmp]=bufer;
        }
}
void countsort(int *ar, int size){
    int max = retMax(ar,size);
    int array[max+1];
	for (int i = 0; i <max+1; i++){
		array[i] = 0;
	}
	
	
    for (int i = 0; i < size; i++){
		array[ar[i]]++;
	}
    
    int key = 0;
    for (int i = 0; i <= max; i++){
		for (int j = key; j < key + array[i]; j++){
			ar[j] = i;
		}
		key += array[i];
	}
}

void checkkeys(int argc, char **argv, int* flags, int& maxsize, int& step){
            if (argc > 1) {
                    for(int i=1;i<argc;i++){
			    if (std::string(argv[i])=="--list"){
			     	
		            }
                            if (std::string(argv[i])=="--meas" or std::string(argv[i])=="all"){
                                    for(int one=0;one<6;one++){
                                            flags[one]=one;
                                    }
                            }
                            else if(std::string(argv[i])=="--size"){
                                    maxsize = atoi(argv[i+1]);
                            }
                            else if(std::string(argv[i])=="--steps"){
                                    step =atoi( argv[i+1]);
                            }
                            else if(std::string(argv[i]) =="--sorts"){
                                    for(int j=1;j+i<argc;j++){
                                            if (std::string(argv[i+j])=="bubble"){
                                                    flags[j-1]=0;
                                            }
                                            else if(std::string(argv[i+j])=="selection"){
                                                    flags[j-1]=1;
                                            }
                                            else if(std::string(argv[i+j])=="count"){
                                                    flags[j-1]=2;
                                            }
                                            else if(std::string(argv[i+j])=="quick"){
                                                    flags[j-1]=3;
                                            }
                                            else if(std::string(argv[i+j])=="insertion"){
                                                    flags[j-1]=4;
                                            }
                                            else if(std::string(argv[i+j])=="merge"){
                                                    flags[j-1]=5;
                                            }
                            }
                            }
            }
            if (maxsize!=step and step==1000){
            	step = maxsize;
            }
            }
            else{
                    cerr<<"No input argiments!"<<endl;
                    exit(1);
            }
        }
	
        void DataBase::CreateSortsTable(){
            request_insert_create("CREATE TABLE IF NOT EXISTS  Sorts(id INTEGER primary key AUTOINCREMENT,nameSort varchar(32));");
            request_insert_create("INSERT or REPLACE INTO Sorts(id,nameSort) VALUES(0,'bubbleSort'),(1,'selectionSort'),(2, 'countsort'),(3, 'quickSort'),(4, 'insertionSort'),(5, 'mergeSort');");
        }
        void DataBase::CreateTimeSortsTable(){
            request_insert_create("CREATE TABLE IF NOT EXISTS  SizeArs(id INTEGER primary key AUTOINCREMENT,sizeAr INTEGER);");
        }
        void DataBase::CreateResSortsTable(){
            request_insert_create("CREATE TABLE IF NOT EXISTS  ResSorts(id INTEGER primary key AUTOINCREMENT,idSort integer,dursort_ms double, idsizeAr integer,FOREIGN KEY(idSort) REFERENCES Sorts(id) on UPDATE CASCADE on DELETE CASCADE,FOREIGN KEY( idsizeAr) REFERENCES SizeArs(id) on UPDATE CASCADE on DELETE CASCADE);");
        }
        DataBase::DataBase(){
            openBd("BigDataBase");
            CreateSortsTable();
            CreateTimeSortsTable();
            CreateResSortsTable();
        }
        DataBase::DataBase(const char* bd_name) {
       	    openBd(bd_name);
            CreateSortsTable();
            CreateTimeSortsTable();
            CreateResSortsTable();
        }
	DataBase::~DataBase(){
	    closeBd();

	 }
        bool DataBase::openBd(const char* bdName) {
            int status = sqlite3_open(bdName, &bd);
            return status;
        }
        bool DataBase::closeBd() {
            int status = sqlite3_close(bd);
	    return status;
        }
        bool DataBase::request_insert_create(const char* sqlString) {
            char* errMsg;
            int er = sqlite3_exec(bd, sqlString, nullptr, nullptr, &errMsg);
            if (er) {
                std::cerr << "error request " << sqlString << " : " << errMsg << std::endl;
            }
            return er;
        }
        bool DataBase::request_select(const char* sqlString, int (*callback)(void*,int,char**,char**), void* outS) {
            char* errMsg;
            int er = sqlite3_exec(bd, sqlString, callback, outS, &errMsg);
            if (er != SQLITE_OK) {
                std::cerr << "error request " << sqlString << " : " << errMsg << std::endl;
                return er;
            }
            return er;
        }

	bool DataBase::SelectidFromArsize(int arsize, int& id){
		id = 0;
		std::string sqlString = "SELECT id from SizeArs WHERE sizeAr = " + to_string(arsize);
		return request_select(sqlString.c_str(), callbackId, &id);
	}


        int DataBase::callbackId(void* outputStruct, int countRec, char** argv, char** colName) {
		int* temp = (int*)outputStruct;
		if (*temp == 0)
			*temp = atoi(argv[0]);
            return 0;
        }
        



