CC = g++
CFLAGS = -std=c++11 -Wall -g -I$(INC_DIR)

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

OBJS = $(OBJ_DIR)/Listas.o \
       $(OBJ_DIR)/pilha.o \
       $(OBJ_DIR)/Fila.o \
       $(OBJ_DIR)/pacote.o \
       $(OBJ_DIR)/armazem.o \
       $(OBJ_DIR)/transporte.o \
       $(OBJ_DIR)/escalonador.o \
       $(OBJ_DIR)/main.o

.PHONY: all clean dirs

all: dirs $(BIN_DIR)/tp2.out

listas.o: $(OBJ_DIR)/Listas.o
pilha.o: $(OBJ_DIR)/pilha.o
fila.o: $(OBJ_DIR)/Fila.o
pacote.o: $(OBJ_DIR)/pacote.o
armazem.o: $(OBJ_DIR)/armazem.o
transporte.o: $(OBJ_DIR)/transporte.o
escalonador.o: $(OBJ_DIR)/escalonador.o
main.o: $(OBJ_DIR)/main.o

dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/tp2.out: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@


$(OBJ_DIR)/Listas.o: $(SRC_DIR)/Listas.cpp $(INC_DIR)/Listas.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/pilha.o: $(SRC_DIR)/pilha.cpp $(INC_DIR)/pilha.hpp $(INC_DIR)/pacote.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/Fila.o: $(SRC_DIR)/Fila.cpp $(INC_DIR)/Fila.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/pacote.o: $(SRC_DIR)/pacote.cpp $(INC_DIR)/pacote.hpp $(INC_DIR)/Listas.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/armazem.o: $(SRC_DIR)/armazem.cpp $(INC_DIR)/armazem.hpp $(INC_DIR)/pilha.hpp $(INC_DIR)/pacote.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/transporte.o: $(SRC_DIR)/transporte.cpp $(INC_DIR)/transporte.hpp $(INC_DIR)/Listas.hpp $(INC_DIR)/Fila.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/escalonador.o: $(SRC_DIR)/escalonador.cpp $(INC_DIR)/escalonador.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/pacote.hpp $(INC_DIR)/armazem.hpp $(INC_DIR)/transporte.hpp $(INC_DIR)/escalonador.hpp \
                    $(INC_DIR)/Listas.hpp $(INC_DIR)/Fila.hpp # Adiciona headers que main pode incluir indiretamente
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/tp2.out