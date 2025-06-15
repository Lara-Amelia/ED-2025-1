CC = g++ 
CFLAGS = -std=c++11 -Wall -Iinclude

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

all: $(BIN_DIR)/tp1.out

$(OBJ_DIR)/ordenadores.o: $(SRC_DIR)/ordenadores.cpp $(INC_DIR)/ordenadores.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ordenadores.cpp -o $(OBJ_DIR)/ordenadores.o

$(OBJ_DIR)/ordenadorUniversal.o: $(SRC_DIR)/ordenadorUniversal.cpp $(INC_DIR)/ordenadores.hpp $(INC_DIR)/ordenadorUniversal.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ordenadorUniversal.cpp -o $(OBJ_DIR)/ordenadorUniversal.o

 $(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/ordenadorUniversal.cpp $(SRC_DIR)/ordenadores.cpp $(INC_DIR)/ordenadores.hpp $(INC_DIR)/ordenadorUniversal.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

$(BIN_DIR)/tp1.out: $(OBJ_DIR)/ordenadores.o $(OBJ_DIR)/ordenadorUniversal.o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/ordenadores.o $(OBJ_DIR)/ordenadorUniversal.o $(OBJ_DIR)/main.o -o $(BIN_DIR)/tp1.out

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/tp1.out