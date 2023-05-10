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
            request_insert_create("CREATE TABLE IF NOT EXISTS  ResSorts(id INTEGER primary key AUTOINCREMENT,idSort integer,dursort_ms double, idsizeAr integer,FOREIGN KEY(idSort) REFERENCES Sorts(id) on UPDATE CASCADE on DELETE CASCADE,FOREIGN KEY( idsizeAr) REFERENCES SizeArs(id) on UPDATE CASCADE on DELETE CASCADE);");
        }

	sqlite3 *bd;
    public:
        DataBase(){
            openBd("BigDataBase");
            CreateSortsTable();
            CreateTimeSortsTable();
            CreateResSortsTable();
        }
        DataBase(const char* bd_name) {
       	    openBd(bd_name);
            CreateSortsTable();
            CreateTimeSortsTable();
            CreateResSortsTable();

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
            for (int i = 0; i < countRec; i++) {
                std::cout << "\t" << colName[i] << " '" << argv[i] << "'";
            }
            std::cout << std::endl;
            return 0;
        }
};

void (*sortsFunc[6])(int*, int) = {bubbleSort, selectionSort, countsort, quickSort, insertionSort, mergeSort};

void sorts(void (*sortName)(int*, int), int* ar, int size) {
    sortName(ar,size);
}


int main(int argc, char **argv){
	int flags[6]={-1,-1,-1,-1,-1,-1};
	std::string insert_stmt;
	int step = 100;
	int maxsize=1000;
	
	DataBase *base= new DataBase();
	if (argc > 1) {
		for(int i=1;i<argc;i++){
			if (std::string(argv[i])=="--meas"){
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
        }
	else{
		cerr<<"No input argiments!"<<endl;
		exit(1);
	}
	for(int mas=0;mas<6;mas++){
		cout<< flags[mas]<< " ";
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
            		base->request_insert_create("INSERT INTO Sorts(nameSort) VALUES(123);");
            		insert_stmt = "INSERT INTO SizeArs(sizeAr) VALUES("s + std::to_string(arsize) + ");";
            		base->request_insert_create(insert_stmt.c_str());
            		insert_stmt = "INSERT INTO ResSorts(dursort_ms) VALUES("s + std::to_string(diff.count()) + ");";
            		base->request_insert_create(insert_stmt.c_str());
            }
            }
            delete[]  ar;
            }		    
	delete base;
	return 0;
}
