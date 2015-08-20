CC = g++
LINK = -lncurses

all: 
	$(CC) $(LINK) $(FILE).cpp -o $(FILE).o
profile:
	$(CC) $(LINK) -pg $(FILE).cpp -o $(FILE).o
game:
	$(CC) $(LINK) main.cpp config.cpp -o bin/Game 
