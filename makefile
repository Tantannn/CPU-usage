all: main

main: main.cpp
	g++ -g main.cpp -lncurses -o main
