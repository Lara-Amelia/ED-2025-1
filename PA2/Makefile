CC = g++ 
CFLAGS = -std=c++11 -Wall -Iinclude

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

OBJS = $(OBJ_DIR)/ListaEncadeada.o $(OBJ_DIR)/ListaAdjacencia.o $(OBJ_DIR)/graph.o $(OBJ_DIR)/main.o
all: $(BIN_DIR)/pa2.out

$(OBJ_DIR)/ListaEncadeada.o: $(SRC_DIR)/ListaEncadeada.cpp $(INC_DIR)/ListaEncadeada.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ListaEncadeada.cpp -o $(OBJ_DIR)/ListaEncadeada.o

$(OBJ_DIR)/ListaAdjacencia.o: $(SRC_DIR)/ListaAdjacencia.cpp $(INC_DIR)/ListaEncadeada.hpp $(INC_DIR)/ListaAdjacencia.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ListaAdjacencia.cpp -o $(OBJ_DIR)/ListaAdjacencia.o 	

$(OBJ_DIR)/graph.o: $(SRC_DIR)/graph.cpp $(INC_DIR)/ListaEncadeada.hpp $(INC_DIR)/ListaAdjacencia.hpp $(INC_DIR)/graph.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/graph.cpp -o $(OBJ_DIR)/graph.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/ListaEncadeada.hpp $(INC_DIR)/ListaAdjacencia.hpp $(INC_DIR)/graph.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o 

$(BIN_DIR)/pa2.out: $(OBJ_DIR)/ListaEncadeada.o $(OBJ_DIR)/ListaAdjacencia.o $(OBJ_DIR)/graph.o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/ListaEncadeada.o $(OBJ_DIR)/ListaAdjacencia.o $(OBJ_DIR)/graph.o $(OBJ_DIR)/main.o -o $(BIN_DIR)/pa2.out

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/pa2.out
