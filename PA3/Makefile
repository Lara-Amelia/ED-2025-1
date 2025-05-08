CC = g++ 
CFLAGS = -std=c++11 -Wall -Iinclude

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

all: $(BIN_DIR)/pa3.out

$(OBJ_DIR)/heap.o: $(SRC_DIR)/heap.cpp $(INC_DIR)/heap.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/heap.cpp -o $(OBJ_DIR)/heap.o
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/heap.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o
$(BIN_DIR)/pa3.out: $(OBJ_DIR)/main.o $(OBJ_DIR)/heap.o 
	$(CC) $(CFLAGS) $(OBJ_DIR)/main.o $(OBJ_DIR)/heap.o -o $(BIN_DIR)/pa3.out

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/pa3.out
