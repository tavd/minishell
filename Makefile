# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irsander <irsander@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 13:27:31 by irsander          #+#    #+#              #
#    Updated: 2024/06/17 13:29:42 by irsander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

INCL = -I ./incl -I $(LIB_DIR)/libft -I $(LIB_DIR)/ft_printf

LIB_DIR = lib
OBJ_DIR = src/obj
SRC_DIR = src

FILES = main.c \

SRC = $(addprefix $(SRC_DIR)/, $(FILES))	
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

LIBFT = $(LIB_DIR)/libft/libft.a
PRINTF = $(LIB_DIR)/ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $^ $(INCL) $(CFLAGS) -o $(NAME)

$(PRINTF):
	make -C $(LIB_DIR)/ft_printf

$(LIBFT):
	make -C $(LIB_DIR)/libft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< $(INCL) $(CFLAGS) -o $@ 

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIB_DIR)/ft_printf
	$(MAKE) clean -C $(LIB_DIR)/libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_DIR)/ft_printf
	$(MAKE) fclean -C $(LIB_DIR)/libft

re: fclean all

.PHONY: all clean make fclean re