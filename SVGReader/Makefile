CC = g++
CFLAGS = -O2 -Wall -Wextra -g
LFLAGS = -ltinyxml
INC = -Iinclude/
SRC = $(wildcard src/*.cpp)
EXE = bin/plotter

all:
	$(CC) -o $(EXE) $(INC) $(SRC) $(CFLAGS) $(LFLAGS)

run:
	./$(EXE)
