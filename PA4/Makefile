CC = g++ 
CFLAGS = -std=c++11 -Wall -Iinclude

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

all: $(BIN_DIR)/pa4.out

$(OBJ_DIR)/unionFind.o: $(SRC_DIR)/unionFind.cpp $(INC_DIR)/unionFind.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/unionFind.cpp -o $(OBJ_DIR)/unionFind.o
$(OBJ_DIR)/minHeap.o: $(SRC_DIR)/minHeap.cpp $(INC_DIR)/minHeap.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/minHeap.cpp -o $(OBJ_DIR)/minHeap.o	
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/unionFind.hpp $(INC_DIR)/minHeap.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o
$(BIN_DIR)/pa4.out: $(OBJ_DIR)/main.o $(OBJ_DIR)/unionFind.o $(OBJ_DIR)/minHeap.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/main.o  $(OBJ_DIR)/unionFind.o $(OBJ_DIR)/minHeap.o -o $(BIN_DIR)/pa4.out

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/pa4.out