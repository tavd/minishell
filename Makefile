# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 13:27:31 by irsander          #+#    #+#              #
#    Updated: 2024/09/04 18:50:09 by tavdiiev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror #-g -fsanitize=address
LDFLAGS		= -lreadline

LIB_DIR = libft
LIBFT = $(LIB_DIR)/libft.a
export LIBFT_MODULES = bool string stdio stdlib

BUILD_PATH = build
INCLUDES_FLAGS = -I incl/ -I libft/include

#================================================================================

FILES_SRC := \
	main.c \
	lexer/lexer.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/pwd.c \
	builtins/export.c \
	builtins/unset.c \
	builtins/cd.c \
	builtins/exit.c \
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
	utils/init_data.c \

SRC_DIR = src
FILES_SRC := $(addprefix $(SRC_DIR)/, $(FILES_SRC))
FILES_OBJ := $(patsubst $(SRC_DIR)/%.c, $(BUILD_PATH)/%.o, $(FILES_SRC))

#================================================================================


all: $(NAME)

$(NAME): $(FILES_OBJ) $(LIBFT)
	$(CC) $^ $(INCLUDES_FLAGS) $(CFLAGS) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIB_DIR)

$(BUILD_PATH)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< $(CFLAGS)$(INCLUDES_FLAGS) -o $@ 

clean:
	rm -rf $(BUILD_PATH)
	$(MAKE) clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean make fclean re
