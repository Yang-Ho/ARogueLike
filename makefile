CC = g++
LINK = -lncurses
STD = -std=c++11

all: 
	$(CC) $(STD) $(LINK) $(FILE).cpp -o $(FILE).o
profile:
	$(CC) $(STD) $(LINK) -pg $(FILE).cpp -o $(FILE).o
game:
	$(CC) $(STD) $(LINK) main.cpp config.cpp rng.cpp monster.cpp -o bin/Game 
