CC = g++
CFLAGS = -std=c++11 -Wall -g -I$(INC_DIR)

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

EXEC = $(BIN_DIR)/tp3.out

# Alvo padrão
all: $(EXEC)

# Compila o executável final (agora com evento.o incluído)
$(EXEC): $(OBJ_DIR)/main.o $(OBJ_DIR)/indicecli.o $(OBJ_DIR)/evento.o
	$(CC) $(CFLAGS) $^ -o $@

# Regras de compilação
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/evento.hpp $(INC_DIR)/indiceCli.hpp $(INC_DIR)/arvoreAVL.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/indicecli.o: $(SRC_DIR)/indiceCli.cpp $(INC_DIR)/indiceCli.hpp $(INC_DIR)/evento.hpp $(INC_DIR)/arvoreAVL.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/evento.o: $(SRC_DIR)/evento.cpp $(INC_DIR)/evento.hpp
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa arquivos gerados
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)