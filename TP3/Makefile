CC = g++
CFLAGS = -std=c++11 -Wall -g -I$(INC_DIR)

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

indicecli.o: $(OBJ_DIR)/indicecli.o
arvoreAVL.o: $(OBJ_DIR)/arvoreAVL.o

$(OBJ_DIR)/arvoreAVL.o: $(SRC_DIR)/arvoreAVL.cpp $(INC_DIR)/arvoreAVL.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/arvoreAVL.cpp -o $(OBJ_DIR)/arvoreAVL.o

$(OBJ_DIR)/indicecli.o: $(SRC_DIR)/indiceCli.cpp $(INC_DIR)/indiceCli.hpp $(INC_DIR)/evento.hpp $(INC_DIR)/arvoreAVL.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/indiceCli.cpp -o $(OBJ_DIR)/indicecli.o