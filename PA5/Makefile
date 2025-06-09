CC = g++ 
CFLAGS = -std=c++11 -Wall -Iinclude

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

all: $(BIN_DIR)/pa5.out

$(OBJ_DIR)/Set.o: $(SRC_DIR)/Set.cpp $(INC_DIR)/Set.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Set.cpp -o $(OBJ_DIR)/Set.o
$(OBJ_DIR)/main.o: $(SRC_DIR)/Set.cpp  $(SRC_DIR)/main.cpp $(INC_DIR)/Set.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

$(BIN_DIR)/pa5.out: $(OBJ_DIR)/main.o $(OBJ_DIR)/Set.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/main.o $(OBJ_DIR)/Set.o -o $(BIN_DIR)/pa5.out

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/pa5.out