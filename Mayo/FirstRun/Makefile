CC = g++ -std=gnu++11
all: main.exe

Script.o: Script.cpp Script.h
	$(CC) Script.cpp -c -g
main.o: main.cpp
	$(CC) main.cpp -c -g
main.exe: main.o Script.o
	$(CC) main.o Script.o -o main.exe -g
