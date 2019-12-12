CC = g++ -std=gnu++11
all: main.exe

Script.o: Script.cpp Script.h
	$(CC) Script.cpp -c -g
Worker.o: Worker.cpp Worker.h
	$(CC) Worker.cpp -c -g
SuperQ.o: SuperQ.cpp SuperQ.h
	$(CC) SuperQ.cpp -c -g
main.o: main.cpp
	$(CC) main.cpp -c -g
main.exe: main.o Script.o Worker.o SuperQ.o
	$(CC) main.o Script.o Worker.o SuperQ.o -o main.exe -g
