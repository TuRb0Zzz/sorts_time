#include <iostream>
#include <chrono>
#include "sorts.h"
#include "arraywork.h"
#include "sqlite3.h"
#include <cassert>
using namespace std;
// the class is created here, because the problem with the creation in the file
class DataBase{
    private:	
        void CreateSortsTable(){
            request_insert_create("CREATE TABLE IF NOT EXISTS  Sorts(id INTEGER primary key AUTOINCREMENT,nameSort varchar(32));");
        }
        void CreateTimeSortsTable(){
            request_insert_create("CREATE TABLE IF NOT EXISTS  SizeArs(id INTEGER primary key AUTOINCREMENT,sizeAr INTEGER);");
        }
        void CreateResSortsTable(){
            request_insert_create("CREATE TABLE IF NOT EXISTS  ResSorts(id INTEGER primary key AUTOINCREMENT,idSort integer,dursort_ms integer, idsizeAr integer,FOREIGN KEY(idSort) REFERENCES Sorts(id) on UPDATE CASCADE on DELETE CASCADE,FOREIGN KEY( idsizeAr) REFERENCES SizeArs(id) on UPDATE CASCADE on DELETE CASCADE);");
        }
    public:
	sqlite3 *bd;
        DataBase(){
	    openBd("BigDataBase");
            CreateSortsTable();
            CreateTimeSortsTable();
            CreateResSortsTable();
	    closeBd();
        }
	~DataBase(){
	    closeBd();
	 }
        bool openBd(const char* bdName) {
            int status = sqlite3_open(bdName, &bd);
            assert(status == SQLITE_OK);

            return status;
        }
        bool closeBd() {
            int status = sqlite3_close(bd);
            assert(status == SQLITE_OK);
            return status;
        }
        bool request_insert_create(const char* sqlString) {
            char* errMsg;
            int er = sqlite3_exec(bd, sqlString, nullptr, nullptr, &errMsg);
            if (er) {
                std::cerr << "error request " << sqlString << " : " << errMsg << std::endl;
            }
            return er;
        }
        bool request_select(const char* sqlString) {
            char* errMsg;
            int er = sqlite3_exec(bd, sqlString, callback, nullptr, &errMsg);

            if (er != SQLITE_OK) {
                std::cerr << "error request " << sqlString << " : " << errMsg << std::endl;
            }
            assert(er == SQLITE_OK);
            return er;
        }
        static int callback(void* outputStruct, int countRec, char** argv, char** colName) {
            //void* -- c-style
            //outputStructure allow to return back the data for processing....
            for (int i = 0; i < countRec; i++) {
                std::cout << "\t" << colName[i] << " '" << argv[i] << "'";
            }
            std::cout << std::endl;
            return 0;
        }
};




int main(int argc, char **argv){
	bool flags[6]={0,0,0,0,0,0};
	std::string insert_stmt;
	int step = 100;
	int maxsize=1000;
	
	DataBase *base= new DataBase();
	if (argc>1){
		for(int i=1;i<argc;i++){
			if (std::string(argv[i])=="--meas"){
				flags[0]=1,flags[1]=1,flags[2]=1,flags[3]=1,flags[4]=1,flags[5]=1;
			}
			else if(std::string(argv[i])=="--size"){
				maxsize = atoi(argv[i+1]);
			}
			else if(std::string(argv[i])=="--steps"){
				step =atoi( argv[i+1]);
			}
			else if(std::string(argv[i]) =="--sorts"){
				if (std::string(argv[i+1])=="bubble"){
					flags[0]=1,flags[1]=0,flags[2]=0,flags[3]=0,flags[4]=0,flags[5]=0;
				}
				else if(std::string(argv[i+1])=="selection"){
				 	flags[0]=0,flags[1]=1,flags[2]=0,flags[3]=0,flags[4]=0,flags[5]=0;    
				}
				else if(std::string(argv[i+1])=="count"){
					flags[0]=0,flags[1]=0,flags[2]=1,flags[3]=0,flags[4]=0,flags[5]=0;
				}
				else if(std::string(argv[i+1])=="quick"){
					flags[0]=0,flags[1]=0,flags[2]=0,flags[3]=1,flags[4]=0,flags[5]=0;
				}
				else if(std::string(argv[i+1])=="insertion"){
					flags[0]=0,flags[1]=0,flags[2]=0,flags[3]=0,flags[4]=1,flags[5]=0;
				}
				else if(std::string(argv[i+1])=="merge"){
					flags[0]=0,flags[1]=0,flags[2]=0,flags[3]=0,flags[4]=0,flags[5]=1;
				}
			}

	}
	}
	else{
		cerr<<"No input argiments!"<<endl;
		exit(1);
	}
	base->openBd("BigDataBase\0");
            std::chrono::time_point<std::chrono::high_resolution_clock> start;
            std::chrono::time_point<std::chrono::high_resolution_clock> end;
            chrono::duration<double> diff;
        for(int arsize = step; arsize <= maxsize; arsize += step){
            int* ar = new int[arsize];
            randomFilling(ar , arsize ,0 , 999);

            if ( flags[0] ){
                    start = chrono::high_resolution_clock::now();
                    bubbleSort(ar,arsize);
                    end = chrono::high_resolution_clock::now();
		    base->request_insert_create("INSERT INTO Sorts(nameSort) VALUES('bubblesort');");
		    insert_stmt = "INSERT INTO SizeArs(sizeAr) VALUES("s + std::to_string(arsize) + ");";
		    base->request_insert_create(insert_stmt.c_str());
		    insert_stmt = "INSERT INTO ResSorts(dursort_ms) VALUES("s + std::to_string(diff.count()) + ");";
		    base->request_insert_create(insert_stmt.c_str());
            }		    
 
            if ( flags[1]){
                start = chrono::high_resolution_clock::now();
                selectionSort(ar,arsize);
                end = chrono::high_resolution_clock::now();
                diff = end - start;
		base->request_insert_create("INSERT INTO Sorts(nameSort) VALUES('selectionsort');");
		insert_stmt = "INSERT INTO SizeArs(sizeAr) VALUES("s + std::to_string(arsize) + ");";
		base->request_insert_create(insert_stmt.c_str());
		insert_stmt = "INSERT INTO ResSorts(dursort_ms) VALUES("s + std::to_string(diff.count()) + ");";
		base->request_insert_create(insert_stmt.c_str());
            }

            if ( flags[2] ){
                start = chrono::high_resolution_clock::now();
                countsort(ar,arsize);
                end = chrono::high_resolution_clock::now();
                diff = end - start;
		base->request_insert_create("INSERT INTO Sorts(nameSort) VALUES('countsort');");
		insert_stmt = "INSERT INTO SizeArs(sizeAr) VALUES("s + std::to_string(arsize) + ");";
		base->request_insert_create(insert_stmt.c_str());
		insert_stmt = "INSERT INTO ResSorts(dursort_ms) VALUES("s + std::to_string(diff.count()) + ");";
		base->request_insert_create(insert_stmt.c_str());
            }

            if ( flags[3] ){
                start = chrono::high_resolution_clock::now();
                quickSort(ar,arsize);
                end = chrono::high_resolution_clock::now();
                diff = end - start;
		base->request_insert_create("INSERT INTO Sorts(nameSort) VALUES('quicksort');");
		insert_stmt = "INSERT INTO SizeArs(sizeAr) VALUES("s + std::to_string(arsize) + ");";
		base->request_insert_create(insert_stmt.c_str());
		insert_stmt = "INSERT INTO ResSorts(dursort_ms) VALUES("s + std::to_string(diff.count()) + ");";
		base->request_insert_create(insert_stmt.c_str());
	   }

            if ( flags[4] ){
                start = chrono::high_resolution_clock::now();

                insertionSort(ar,arsize);

                end = chrono::high_resolution_clock::now();
                diff = end - start;
		base->request_insert_create("INSERT INTO Sorts(nameSort) VALUES('insertionsort');");
		insert_stmt = "INSERT INTO SizeArs(sizeAr) VALUES("s + std::to_string(arsize) + ");";
		base->request_insert_create(insert_stmt.c_str());
		insert_stmt = "INSERT INTO ResSorts(dursort_ms) VALUES("s + std::to_string(diff.count()) + ");";
		base->request_insert_create(insert_stmt.c_str());
	    }

            if ( flags[5] ){
                start = chrono::high_resolution_clock::now();

                mergeSort(ar,arsize);

                end = chrono::high_resolution_clock::now();
                diff = end - start;
		base->request_insert_create("INSERT INTO Sorts(nameSort) VALUES('mergesort');");
		insert_stmt = "INSERT INTO SizeArs(sizeAr) VALUES("s + std::to_string(arsize) + ");";
		base->request_insert_create(insert_stmt.c_str());
		insert_stmt = "INSERT INTO ResSorts(dursort_ms) VALUES("s + std::to_string(diff.count()) + ");";
		base->request_insert_create(insert_stmt.c_str());
	    }
            delete[]  ar;
            }
	delete base;
	return 0;



}
