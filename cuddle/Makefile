##
## EPITECH PROJECT, 2024
## Nouveau dossier [WSL: kali-linux]
## File description:
## Makefile
##

# Nom de la bibliothèque
NAME = libcuddle.a

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

# Fichiers sources et objets
SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Fichiers de test
TEST_DIR = tests
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_EXEC = cuddle_test

# Commandes principales
all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "✔ Compilation terminée : $(NAME)"

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Tests automatiques
tests: $(NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_OBJ) -L. -lcuddle
	@echo "🚀 Lancement des tests..."
	@./$(TEST_EXEC)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ_DIR)
	@echo "🗑 Suppression des fichiers objets."

# Nettoyage complet
fclean: clean
	@rm -f $(NAME) $(TEST_EXEC)
	@echo "🗑 Suppression de $(NAME) et des exécutables de test."

# Recompilation complète
re: fclean all

.PHONY: all clean fclean re tests
