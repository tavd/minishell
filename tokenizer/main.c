#include "tokenizer.h"

#include <stdio.h>
int	main(int argc, char **argv)
{
	t_lexer l;
	t_token	t;
	
	t = (t_token){0};
	if (argc != 2)
		return 0;
	char	*str = argv[1];
	l = create_tokenizer(str, str + ft_strlen(str));
	while (get_next_token(&l, &t))
	{
		printf("(%s:%.*s) at lexer[%li]\n", (char *)SYMBOL_TABLE[t.id][SYMBOL], (int)(t.end - t.begin), t.begin, l.cur);
		t = (t_token){0};
	}
}
