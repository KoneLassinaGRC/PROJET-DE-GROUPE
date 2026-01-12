# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -I./src

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Fichiers sources et objets
SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Nom de l'exécutable principal
TARGET = NetFlow-Optimizer

# Compiler le projet
all: $(TARGET)

# Lien final
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

# Compiler les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer les fichiers objets et l’exécutable
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(TARGET)

# Compiler et exécuter les tests
test: CFLAGS += -DTEST
test: $(OBJS)
	$(CC) $(CFLAGS) $(TEST_DIR)/*.c $(OBJS) -o $(BIN_DIR)/test_exec
	$(BIN_DIR)/test_exec
