all: test_sqlite

test_sqlite: main1.o sqlite3.o sorts.o arraywork.o
	g++ main1.o sqlite3.o sorts.o arraywork.o -ldl -lpthread
	
main1.o: main1.cpp
	g++ -c main1.cpp
	
sqlite3.o: sqlite3.c sqlite3.h
	gcc -c sqlite3.c -lpthread -ldl 
	
sorts.o: sorts.c
	g++ -c sorts.c
	
arraywork.o: arraywork.c
	g++ -c arraywork.c
clean:
	rm -rf *.o *.exe *.out
