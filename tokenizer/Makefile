CFLAGS = -g
CC = cc
INCLUDE_FLAGS = -I. -Iinclude
LIB_FLAGS = -L. -lft


SRC = tokenizer.c parser.c
OBJ = $(SRC:.c=.o)

NAME = main

all: main

$(NAME): $(OBJ)
	$(CC) $(INCLUDE_FLAGS) $^ $(LIB_FLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
