# Compilador e flags
CC = g++
CFLAGS = -std=c++11 -Wall -g -I$(INC_DIR)

# Diretórios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Executável final
EXEC = $(BIN_DIR)/tp3.out

# Lista de objetos
OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/indicecli.o \
       $(OBJ_DIR)/evento.o \
       $(OBJ_DIR)/indicePacs.o \
       $(OBJ_DIR)/indicePacsTempo.o

# Alvo padrão
all: $(EXEC)

# Compilação do executável final
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compilação individual dos arquivos
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/evento.hpp $(INC_DIR)/indiceCli.hpp $(INC_DIR)/arvoreAVL.hpp $(INC_DIR)/indicePacs.hpp $(INC_DIR)/indicePacTempo.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/indicecli.o: $(SRC_DIR)/indiceCli.cpp $(INC_DIR)/indiceCli.hpp $(INC_DIR)/evento.hpp $(INC_DIR)/arvoreAVL.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/evento.o: $(SRC_DIR)/evento.cpp $(INC_DIR)/evento.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/indicePacs.o: $(SRC_DIR)/indicePacs.cpp $(INC_DIR)/indicePacs.hpp $(INC_DIR)/evento.hpp $(INC_DIR)/arvoreAVL.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/indicePacsTempo.o: $(SRC_DIR)/indicePacsTempo.cpp $(INC_DIR)/indicePacTempo.hpp $(INC_DIR)/evento.hpp $(INC_DIR)/arvoreAVL.hpp
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa arquivos gerados
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)