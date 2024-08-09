# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 13:27:31 by irsander          #+#    #+#              #
#    Updated: 2024/08/07 20:16:41 by tavdiiev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror #-g -fsanitize=address
LDFLAGS		= -lreadline

LIB_DIR = libft
INCL = -I ./incl -I $(LIB_DIR)/incl

FILES = main.c \
lexer/lexer.c \
builtins/echo.c \
builtins/env.c \
builtins/pwd.c \
builtins/export.c \
builtins/unset.c \
builtins/cd.c \
env_utils/env_set_unset.c \
env_utils/env_utils_functions.c \
execution/execute_command.c \
execution/execute.c \
execution/get_path.c \
execution/utils.c \
redirections/io.c \
redirections/pipe.c \
utils/error.c \
utils/free_close.c \
utils/exit_shell.c \
utils/init_data.c

SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, $(FILES))	

OBJ_DIR = src/obj
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

LIBFT = $(LIB_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $^ $(INCL) $(CFLAGS) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIB_DIR)

# $(OBJ_DIR):
# 	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/lexer
	mkdir -p $(OBJ_DIR)/builtins
	mkdir -p $(OBJ_DIR)/env_utils
	mkdir -p $(OBJ_DIR)/execution
	mkdir -p $(OBJ_DIR)/utils
	mkdir -p $(OBJ_DIR)/redirections
	$(CC) -c $< $(INCL) $(CFLAGS) -o $@ 

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean make fclean re