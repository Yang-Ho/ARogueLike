CC = g++

LINK = -ltcod

LIB_FLAGS = -L/usr/local/lib -Wl,-rpath -Wl,/usr/local/lib

INCLUDE_FLAGS = -I/usr/include/SDL2 -I/usr/local/include/libtcod

STD = -std=c++14

SOURCE_FILES=main.cpp config.cpp rng.cpp monster.cpp level.cpp

all: 
	$(CC) $(STD) $(LINK) $(FILE).cpp -o $(FILE).o
profile:
	$(CC) $(STD) $(LINK) -pg $(FILE).cpp -o $(FILE).o
game:
	$(CC) $(STD) $(LIB_FLAGS) $(LINK) $(INCLUDE_FLAGS) $(SOURCE_FILES) -o bin/Game 
