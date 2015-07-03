CC = g++
LINK = -lcurses

all: 
	$(CC) $(LINK) $(FILE).cpp -o $(FILE).o
