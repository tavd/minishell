FLAGS = 

CC = cc

INCLUDES = -Iinclude

all: main

main: tokenizer.o
	$(CC) $(INCLUDES) $^ libft.a -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) tokenizer.o

re: clean all
