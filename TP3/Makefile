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
	   $(OBJ_DIR)/indicePacsTempo.o \
	   $(OBJ_DIR)/pacote.o # <--- ADD THIS LINE

# Alvo padrão
all: $(EXEC)

# Cria os diretórios de saída se não existirem
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Alvo 'all' agora depende da criação dos diretórios
all: $(OBJ_DIR) $(BIN_DIR) $(EXEC)

# Compilação do executável final
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compilação individual dos arquivos
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/evento.hpp $(INC_DIR)/indiceCli.hpp $(INC_DIR)/arvoreAVL.hpp $(INC_DIR)/indicePacs.hpp $(INC_DIR)/indicePacTempo.hpp $(INC_DIR)/pacote.hpp # <--- ADD pacote.hpp dependency if directly used in main
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/indicecli.o: $(SRC_DIR)/indiceCli.cpp $(INC_DIR)/indiceCli.hpp $(INC_DIR)/evento.hpp $(INC_DIR)/arvoreAVL.hpp $(INC_DIR)/pacote.hpp # <--- ADD pacote.hpp dependency here
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/evento.o: $(SRC_DIR)/evento.cpp $(INC_DIR)/evento.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/indicePacs.o: $(SRC_DIR)/indicePacs.cpp $(INC_DIR)/indicePacs.hpp $(INC_DIR)/evento.hpp $(INC_DIR)/arvoreAVL.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/indicePacsTempo.o: $(SRC_DIR)/indicePacsTempo.cpp $(INC_DIR)/indicePacTempo.hpp $(INC_DIR)/evento.hpp $(INC_DIR)/arvoreAVL.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/pacote.o: $(SRC_DIR)/pacote.cpp $(INC_DIR)/pacote.hpp # <--- ADD THIS NEW RULE
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa arquivos gerados
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)