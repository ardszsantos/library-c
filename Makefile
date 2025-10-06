# Nome do executável
APP = app

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

# Pega todos os arquivos .c dentro de src e subpastas
SRCS := $(shell find src -name "*.c")
OBJS := $(SRCS:.c=.o)

# Regra padrão
all: $(APP)

# Compila o executável
$(APP): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Regra genérica para objetos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJS) $(APP)

# Compila e executa
run: all
	./$(APP)
