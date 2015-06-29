CC = g++
LINK = -lncurses

all: 
	$(CC) $(LINK) $(FILE).cpp -o $(FILE)
