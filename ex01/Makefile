# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/18 17:45:15 by tcohen            #+#    #+#              #
#    Updated: 2025/08/18 17:46:27 by tcohen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        := RPN
CXX         := c++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++98

SRC         := main.cpp RPN.cpp
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

.PHONY: all clean fclean re