# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/20 17:52:14 by theog             #+#    #+#              #
#    Updated: 2025/09/03 19:54:36 by tcohen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        := PmergeMe
CXX         := c++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++98

SRC         := main.cpp PmergeMe.cpp
OBJ_DIR     := obj
OBJ         := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# === Couleurs pour plus de clarté ===

GREEN := \033[0;32m
BLUE  := \033[0;34m
RESET := \033[0m

# === Règles ===

all: $(NAME)

# Compilation finale
$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "$(GREEN)[✔] Compilation terminée : $(NAME)$(RESET)"

# Compilation des fichiers .o
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)[🧹] Fichiers objets supprimés$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)[🗑] Exécutable supprimé : $(NAME)$(RESET)"

re: fclean all

run1:
	@echo "Exécution de $(NAME) avec 1000 entiers positifs triés..."
	@./$(NAME) $(shell seq 1 1000)

run2:
	@echo "Exécution de $(NAME) avec 3000 entiers positifs aléatoires..."
	@./$(NAME) $(shell shuf -i 1-3000 -n 3000)

run3:
	@echo "Exécution de $(NAME) avec 1000 entiers positifs aléatoires..."
	@./$(NAME) $(shell shuf -i 1-10000 -n 10000)


.PHONY: all clean fclean re run