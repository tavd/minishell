# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irsander <irsander@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 23:08:05 by irsander          #+#    #+#              #
#    Updated: 2024/05/28 15:22:58 by irsander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCL		= ft_printf.h

SRC			=	ft_printf.c \
				ft_printf_utils.c \

OFILES		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OFILES) $(HEADER)
	@ar rcs $(NAME) $?

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@rm -rf $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean make fclean re
