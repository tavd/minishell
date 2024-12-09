#include "tokenizer.h"
#include <stdio.h>

typedef	struct s_lst_cmd
{
	t_lst_embed	lst_data;
	union {
		char	**argv;
		char	*name;
	};
	bool		is_piped;
	char		*infile;
	char		*outfile;
	int		fd_infile;
	int		fd_outfile;

} t_lst_cmd;

#include <errno.h>

void	set_errno(int e)
{
	errno = e;
}

typedef struct vec
{
	void	*data;
	size_t	allocated_size;
	size_t	used_bytes;
}	t_vec;

// NOTE: is not the same as realloc, since we need to pass old_size
void	*ft_realloc(void *old_mem, size_t old_size, size_t new_size)
{
	void	*new_mem;
	
	if (!old_mem)
		return (malloc(new_size));
	if (old_size == new_size)
		return (old_mem);
	new_mem = malloc(new_size);
	if (!new_mem)
		return (NULL);
	if (new_size < old_size)
		ft_memcpy(new_mem, old_mem, new_size);
	else
		ft_memcpy(new_mem, old_mem, old_size);
	free(old_mem);
	return (new_mem);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	len;
	char	*new_str;

	if (ft_strlen(src) < n)
		len = ft_strlen(src);
	else 
		len = n;
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, src, len);
	new_str[len] = '\0';
	return (new_str);
}

t_lst_cmd	build_cmd_from_tokenizer(t_lexer *l)
{
	char	**argv;
	int	argc;
	char	*new_word;
	t_token	cur;
	t_lst_cmd	cmd;

	cmd = (t_lst_cmd){0};
	argc = 0;
	argv = NULL;
	while (get_next_token(l, &cur) && has_id(&cur, WORD))
	{
		//new_vec_size(argv, ++argc * sizeof(char *));
		new_word = ft_strndup(cur.begin, cur.end - cur.begin);
		ft_realloc(argv, argc * sizeof(char *), (argc + 1) * sizeof(char *));// bad
		++argc;
		argv[argc - 1] = new_word;
	}
	ft_realloc(argv, argc * sizeof(char *), (argc + 1) * sizeof(char *));// bad
	argv[argc] = NULL;
	printf("%i", argc);
	// while (get_next_token(l, &cur))
	// {
	// 	if (has_id(SINGLE_QUOTE, &cur)
	// 		next_word = 
	// }
	// next_word
	// while (get_next_token(l, &cur) && !has_id(DOUBLE_QUOTE, &cur))
	// {
	//
	// }
	// while (get_next_token(l, &cur))
	// {
	// 	if (has_id(SINGLE_QUOTE, &cur))
	// 	{
	//
	// 	}
	// 	t = (t_token){0}; // reset token needed?
	// }
	cmd.argv = argv;
	return (cmd);
}

void	get_next_cmd(t_lexer *l)
{
	t_token	t;

	while (get_next_token(l, &t))
	{
		printf("(%s:%.*s) at lexer[%li]\n", (char *)SYMBOL_TABLE[t.id][SYMBOL], (int)(t.end - t.begin), t.begin, l->cur);
		t = (t_token){0};
	}
}

int	main(int argc, char **argv)
{
	t_lexer l;
	t_token	t;
	
	t = (t_token){0};
	if (argc != 2)
		return 0;
	char	*str = argv[1];
	l = create_tokenizer(str, str + ft_strlen(str));
	t_lst_cmd cmd = build_cmd_from_tokenizer(&l);
	printf("%s", cmd.name);

	//get_next_cmd(&l);
	return 0;
}
