# Define o compilador C++
CC = g++

# Define as flags de compilação:
# -std=c++11: Usa o padrão C++11.
# -Wall: Ativa todos os warnings úteis.
# -g: Inclui informações de debug (útil para gdb, etc.)
# -I$(INC_DIR): Adiciona o diretório 'include' para procurar arquivos de cabeçalho.
CFLAGS = -std=c++11 -Wall -g -I$(INC_DIR)

# Define os diretórios do projeto
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Lista todos os arquivos objeto (.o) que precisam ser construídos.
# ATENÇÃO: As barras invertidas (\) para quebrar linha devem ser o ÚLTIMO CARACTERE da linha.
# Não coloque espaços APÓS a barra invertida.
OBJS = $(OBJ_DIR)/Listas.o \
$(OBJ_DIR)/pilha.o \
$(OBJ_DIR)/Fila.o \
$(OBJ_DIR)/pacote.o \
$(OBJ_DIR)/armazem.o \
$(OBJ_DIR)/transporte.o \
$(OBJ_DIR)/escalonador.o \
$(OBJ_DIR)/evento.o \
$(OBJ_DIR)/main.o

# Define alvos "phony" que não correspondem a arquivos físicos.
.PHONY: all clean dirs \
        listas.o pilha.o fila.o pacote.o armazem.o transporte.o escalonador.o evento.o main.o

# -----------------------------------------------------------------------------
# Regras Principais
# -----------------------------------------------------------------------------

# Alvo padrão: 'all' -> constrói o executável final
all: dirs $(BIN_DIR)/tp2.out

# NOVO: Regras individuais para compilar cada arquivo objeto (.o)
# Estes são alvos PHONY que dependem dos alvos .o reais.
listas.o: $(OBJ_DIR)/Listas.o
pilha.o: $(OBJ_DIR)/pilha.o
fila.o: $(OBJ_DIR)/Fila.o
pacote.o: $(OBJ_DIR)/pacote.o
armazem.o: $(OBJ_DIR)/armazem.o
transporte.o: $(OBJ_DIR)/transporte.o
escalonador.o: $(OBJ_DIR)/escalonador.o
evento.o: $(OBJ_DIR)/evento.o
main.o: $(OBJ_DIR)/main.o


# Alvo para criar os diretórios de saída se não existirem
dirs:
# Use '@' para não imprimir o comando no terminal.
# A linha abaixo DEVE começar com um TAB.
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Regra para construir o executável final
# Depende de todos os arquivos objeto listados em $(OBJS).
$(BIN_DIR)/tp2.out: $(OBJS)
# A linha abaixo DEVE começar com um TAB.
	$(CC) $(CFLAGS) $(OBJS) -o $@

# -----------------------------------------------------------------------------
# Regras para os Arquivos Objeto (.o)
# Cada regra especifica como compilar um .cpp em um .o
# Dependências: O arquivo .cpp correspondente e TODOS os .hpp que ele inclui.
# Use '$<' para o primeiro pré-requisito (o .cpp) e '$@' para o alvo (o .o).
# -----------------------------------------------------------------------------

$(OBJ_DIR)/Listas.o: $(SRC_DIR)/Listas.cpp $(INC_DIR)/Listas.hpp
# A linha abaixo DEVE começar com um TAB.
	$(CC) $(CFLAGS) -c $< -o $@

# pilha.cpp inclui pilha.hpp que, por sua vez, inclui pacote.hpp
$(OBJ_DIR)/pilha.o: $(SRC_DIR)/pilha.cpp $(INC_DIR)/pilha.hpp $(INC_DIR)/pacote.hpp
# A linha abaixo DEVE começar com um TAB.
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/Fila.o: $(SRC_DIR)/Fila.cpp $(INC_DIR)/Fila.hpp
# A linha abaixo DEVE começar com um TAB.
	$(CC) $(CFLAGS) -c $< -o $@

# pacote.cpp inclui pacote.hpp que, por sua vez, inclui Listas.hpp
$(OBJ_DIR)/pacote.o: $(SRC_DIR)/pacote.cpp $(INC_DIR)/pacote.hpp $(INC_DIR)/Listas.hpp
# A linha abaixo DEVE começar com um TAB.
	$(CC) $(CFLAGS) -c $< -o $@

# armazem.cpp inclui armazem.hpp que, por sua vez, inclui pilha.hpp e pacote.hpp
$(OBJ_DIR)/armazem.o: $(SRC_DIR)/armazem.cpp $(INC_DIR)/armazem.hpp $(INC_DIR)/pilha.hpp $(INC_DIR)/pacote.hpp
# A linha abaixo DEVE começar com um TAB.
	$(CC) $(CFLAGS) -c $< -o $@

# transporte.cpp inclui transporte.hpp que, por sua vez, inclui Listas.hpp e Fila.hpp
$(OBJ_DIR)/transporte.o: $(SRC_DIR)/transporte.cpp $(INC_DIR)/transporte.hpp $(INC_DIR)/Listas.hpp $(INC_DIR)/Fila.hpp
# A linha abaixo DEVE começar com um TAB.
	$(CC) $(CFLAGS) -c $< -o $@

# escalonador.cpp inclui escalonador.hpp
$(OBJ_DIR)/escalonador.o: $(SRC_DIR)/escalonador.cpp $(INC_DIR)/escalonador.hpp $(INC_DIR)/evento.hpp # Adicionado Evento.hpp como dependência
# A linha abaixo DEVE começar com um TAB.
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para evento.o: Depende de evento.cpp e seus includes (pacote.hpp)
$(OBJ_DIR)/evento.o: $(SRC_DIR)/evento.cpp $(INC_DIR)/evento.hpp $(INC_DIR)/pacote.hpp
# A linha abaixo DEVE começar com um TAB.
	$(CC) $(CFLAGS) -c $< -o $@

# main.cpp inclui vários headers.
$(OBJ_DIR)/main.o: $(SRC_DIR)/mainv2.cpp $(INC_DIR)/pacote.hpp $(INC_DIR)/armazem.hpp $(INC_DIR)/transporte.hpp $(INC_DIR)/escalonador.hpp \
                    $(INC_DIR)/Listas.hpp $(INC_DIR)/Fila.hpp $(INC_DIR)/evento.hpp
# A linha abaixo DEVE começar com um TAB.
	$(CC) $(CFLAGS) -c $< -o $@

# -----------------------------------------------------------------------------
# Regras de Limpeza
# -----------------------------------------------------------------------------

# Alvo 'clean': remove todos os arquivos objeto e o executável
clean:
# A linha abaixo DEVE começar com um TAB.
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/tp2.out