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

		sqlite3 *bd;
    public:
        DataBase(){
			openBd("BigDataBase");
            CreateSortsTable();
            CreateTimeSortsTable();
            CreateResSortsTable();
		//	closeBd();
        }
		DataBase(const char* bd_name) {}
	~DataBase(){
	    closeBd();

	 }
        bool openBd(const char* bdName) {
            int status = sqlite3_open(bdName, &bd);
#ifdef DBG
            assert(status == SQLITE_OK);
#endif

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
        bool request_select(const char* sqlString, void (*callback)(...)) {
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
			LL *temp = static_cast<LL*>(outputStruct);
            //outputStructure allow to return back the data for processing....
            for (int i = 0; i < countRec; i++) {
                std::cout << "\t" << colName[i] << " '" << argv[i] << "'";
            }
            std::cout << std::endl;
            return 0;
        }
};


class BD {

	public :
		virtual ~BD() = 0;
};

class SortsBd : public BD {

	public :
		static int callBack();
		LL* getSortsBySize(....);
};


#define BUBBLE	1
#define QUICK	2

enum NameFlags{
	BubbleSort = 0,
	QuckSorts,

};
void (*sortsFunc[6])(int*, int) = {bubbleSort, quickSort....};

void sorts(void (*sortName)(unsigned int*, int), unsigned int* ar, int size) {

}


int main(int argc, char **argv){
	bool flags[6]={0,0,0,0,0,0};	//ВСЯ суть работы!!!
	int sortsType = 0;
	std::string insert_stmt;
	int step = 100;
	int maxsize=1000;
	
	DataBase *base= new DataBase();
	if (argc > 1) {
		for(int i=1;i<argc;i++){
			if (std::string(argv[i])=="--meas"){
				flags[BubbleSorts]=0,flags[1]=0,flags[2]=0,flags[3]=0,flags[4]=0,flags[5]=0;
			}
			else if(std::string(argv[i])=="--size"){
				maxsize = atoi(argv[i+1]);
			}
			else if(std::string(argv[i])=="--steps"){
				step =atoi( argv[i+1]);
			}
			else if(std::string(argv[i]) =="--sorts"){
				for (int k = i; k < ....; k++) {

					if (std::string(argv[i+1])=="bubble"){
						flags[k-i]=1;
					}
				else if(std::string(argv[i+1])=="selection"){
				 	flags[1]=1;
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
			if (flags[0] == 0) {
				for (int i = 0; i < 6; i++) {
					flags[i] = i+1;
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
                    start = chrono::high_resolution_clock::now();
			sorts(sortsFunc[flags[i]], ar, 999);
                    end = chrono::high_resolution_clock::now();


					std::map<int /*id sort in bs*/, std::string /*sort name*/> nameSortsToInt = {{1, "bubbleSort"}, {2, ..}};
					sprintf("insert into Sorts(nameSort

			sprintf(...)
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
		base->_
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
