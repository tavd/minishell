FLAGS = 

CC = cc


NAME = main
INCLUDES = -Iinclude

all: main

$(NAME): tokenizer.o
	$(CC) $(INCLUDES) $^ libft.a -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) tokenizer.o

fclean: clean
	$(RM) $(NAME)

re: fclean all
