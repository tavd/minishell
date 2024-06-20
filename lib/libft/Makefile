# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irsander <irsander@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 16:36:41 by irsander          #+#    #+#              #
#    Updated: 2024/06/20 18:22:37 by irsander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIB_DIR		= lib
INCL		= -I ./incl -I $(LIB_DIR)/libft

FILES		=	char_checks/ft_isalnum.c \
				char_checks/ft_isalpha.c \
				char_checks/ft_isascii.c \
				char_checks/ft_isdigit.c \
				char_checks/ft_isprint.c \
				conversions/ft_atoi.c \
				conversions/ft_itoa.c \
				conversions/ft_tolower.c \
				conversions/ft_toupper.c \
				get_next_line/get_next_line_utils.c \
				get_next_line/get_next_line.c \
				list_ops/ft_lstadd_back.c \
				list_ops/ft_lstadd_front.c \
				list_ops/ft_lstclear.c \
				list_ops/ft_lstdelone.c \
				list_ops/ft_lstiter.c \
				list_ops/ft_lstlast.c \
				list_ops/ft_lstmap.c \
				list_ops/ft_lstnew.c \
				list_ops/ft_lstsize.c \
				mem_ops/ft_bzero.c \
				mem_ops/ft_calloc.c \
				mem_ops/ft_memchr.c \
				mem_ops/ft_memcmp.c \
				mem_ops/ft_memcpy.c \
				mem_ops/ft_memmove.c \
				mem_ops/ft_memset.c \
				printf/ft_printf_utils.c \
				printf/ft_printf.c \
				put_ops/ft_putchar_fd.c \
				put_ops/ft_putchar.c \
				put_ops/ft_putendl_fd.c \
				put_ops/ft_putnbr_fd.c \
				put_ops/ft_putstr_fd.c \
				put_ops/ft_putstr.c \
				str_ops/ft_split.c \
				str_ops/ft_strchr.c \
				str_ops/ft_strdup.c \
				str_ops/ft_striteri.c \
				str_ops/ft_strjoin.c \
				str_ops/ft_strlcat.c \
				str_ops/ft_strlcpy.c \
				str_ops/ft_strlen.c \
				str_ops/ft_strmapi.c \
				str_ops/ft_strncmp.c \
				str_ops/ft_strnstr.c \
				str_ops/ft_strrchr.c \
				str_ops/ft_strtrim.c \
				str_ops/ft_substr.c \

SRC_DIR		= src
SRC			= $(addprefix $(SRC_DIR)/, $(FILES))

OBJ_DIR		= src/obj
OFILES		= $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)/char_checks
	@ mkdir -p $(OBJ_DIR)/conversions
	@ mkdir -p $(OBJ_DIR)/get_next_line
	@ mkdir -p $(OBJ_DIR)/list_ops
	@ mkdir -p $(OBJ_DIR)/mem_ops
	@ mkdir -p $(OBJ_DIR)/printf
	@ mkdir -p $(OBJ_DIR)/put_ops
	@ mkdir -p $(OBJ_DIR)/str_ops
	$(CC) $(CFLAGS) $(INCL) -c -o $@ $<
	
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean make fclean re