#include <iostream>
#include <chrono>
#include "sorts.h"
#include "arraywork.h"
#include "sqlite3.h"
#include <cassert>

using namespace std;

void (*sortsFunc[6])(int*, int) = {bubbleSort, selectionSort, countsort, quickSort, insertionSort, mergeSort};

void sorts(void (*sortName)(int*, int), int* ar, int size) {
    sortName(ar,size);
}


int main(int argc, char **argv){
	int flags[6]={ -1, -1, -1, -1, -1, -1 };
	int maxsize = 1000, step = maxsize;
	int id;
	int list=0;
	int exportbd=0;
	FILE* f;
	DataBase *base = new DataBase();
	checkkeys(argc, argv, flags, maxsize, step,list,exportbd);
	if (list==1){
		base->selectlist("Select Rs.id, Sa.sizeAr, S.nameSort, Rs.dursort_ms FROM ResSorts Rs INNER JOIN SizeArs Sa on Sa.id = Rs.idsizeAr INNER JOIN Sorts S on S.id = Rs.idSort;");
		exit(0);
	}
	else if(exportbd==1){
		base->exportbd("Select Rs.id, Sa.sizeAr, S.nameSort, Rs.dursort_ms FROM ResSorts Rs INNER JOIN SizeArs Sa on Sa.id = Rs.idsizeAr INNER JOIN Sorts S on S.id = Rs.idSort;",f);
		exit(0);
	}
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> end;
        chrono::duration<double> diff;
        
        for(int arsize = step; arsize <= maxsize; arsize += step){
            int* ar = new int[arsize];
            randomFilling(ar , arsize ,0 , 999);
	    for(int SortsType=0;SortsType<6;SortsType++){
	    	if (flags[SortsType]!=-1){
            		start = chrono::high_resolution_clock::now();
            		sorts(sortsFunc[flags[SortsType]], ar, arsize);
			end = chrono::high_resolution_clock::now();
			diff = end - start;
			base->SelectidFromArsize(arsize,id);
			if (id == 0){
            			base->request_insert_create(sqlite3_mprintf("INSERT INTO SizeArs(sizeAr) VALUES(%d);",arsize));
				base->SelectidFromArsize(arsize,id);
				base->request_insert_create(sqlite3_mprintf("INSERT INTO ResSorts(idSort,dursort_ms,idsizeAr) VALUES(%d,%e,%d);",flags[SortsType],diff.count(),id));
			}
			else{
				base->request_insert_create(sqlite3_mprintf("INSERT INTO ResSorts(idSort,dursort_ms,idsizeAr) VALUES(%d,%e,%d);",flags[SortsType],diff.count(),id));
			}
            }
            }
            delete[]  ar;
            }		    
	delete base;
	return 0;
}
