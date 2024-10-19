/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:00:34 by mzwart            #+#    #+#             */
/*   Updated: 2024/10/06 23:44:33 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/bool.h"
#include "libft/libft.h"

#include <limits.h>
#include <unistd.h>

#include <stdlib.h>

// remove eventually
#include <stdio.h>
#include <string.h>

// TODO: make it possible for heredoc to set a word as END delimiter...
enum e_identifiers
{
	END,
	WORD,
	SPACE = ' ',
	SET_ENV = '=',
	ENV_VAR = '$',
	PIPE = '|',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	SINGLE_QUOTE = '\"',
	DOUBLE_QUOTE = '\'',

	// ... not sure about these yet
	NEW_LINE = '\n',
	HEREDOC_END,
};

struct s_tokenizer {
	char	*input;
};

typedef struct s_token {
	char			*text;
	ssize_t			length;
	enum e_identifiers	identifier;
}	t_token;

typedef struct s_token_node
{
	t_token			token;
	struct s_token_node	*next;
} t_token_node;

// END is also required here since array of chars needs to be null-terminated
const static char	SINGLE_CHAR_TOKENS[8] = {
	SINGLE_QUOTE, DOUBLE_QUOTE, REDIRECT_IN, REDIRECT_OUT,
	PIPE, SET_ENV, ENV_VAR, END
};

// combine?...
const static char	WORD_DELIMITERS[9] = {
	SPACE, SINGLE_QUOTE, DOUBLE_QUOTE, REDIRECT_IN, REDIRECT_OUT,
	PIPE, SET_ENV, ENV_VAR, END
};

//=============================================================================

void	init_tokenizer(struct s_tokenizer *tokenizer, char *data)
{
	tokenizer->input = data;
}

// NOTE: Is it needed to add identifier for double character token_count?
t_token	tokenize_one_token(struct s_tokenizer *tokenizer)
{
	char		*str;
	t_token		token;

	if (!tokenizer->input)
		return ((t_token){.text = NULL, .length = 0, .identifier = 0});
	str = tokenizer->input;
	token.text = str;
	token.identifier = (enum e_identifiers)*str;
	token.length = 0;
	while (str[token.length] && str[token.length] == SPACE)
		++token.length;
	if (str[token.length] == END || token.length > 0)
	{
		tokenizer->input += token.length;
		return (token);
	}
	if (strchr(SINGLE_CHAR_TOKENS, token.identifier))
	{
		token.length += 1;
		tokenizer->input += 1;
		return (token);
	}
	token.identifier = WORD;
	while (strchr(WORD_DELIMITERS, str[token.length]) == NULL)
		++token.length;
	tokenizer->input += token.length;
	return (token);
}

void	free_data(void *data)
{
	free(data);
}

t_list	*tokenize_all_tokens(struct s_tokenizer *tokenizer)
{
	t_list	*head;
	t_list	*new_node;
	t_token	*tok_ptr;
	t_token	token;

	head	= NULL;
	token.identifier = 1;
	while (token.identifier != END)
	{
		tok_ptr = (t_token *)malloc(sizeof(t_token));
		new_node = ft_lstnew(NULL);
		if (!new_node || !tok_ptr)
		{
			ft_lstclear(&head, &free_data);
			return (NULL);
		}
		token = tokenize_one_token(tokenizer);
		*tok_ptr = token;
		new_node->content = (void *)tok_ptr;
		ft_lstadd_back(&head, new_node);
	}
	return (head);
}

// TODO: Tokenize once, get the count, then malloc for that count
int main(int argc, char **argv)
{
	struct s_tokenizer tokenizer;
	t_token		token;
	int		token_count;
	t_list	*lst;
	int	i;
	int	size;

	char	*buf = malloc(256);
	i = 1;
	size = 0;
	while (i < argc)
	{
		size += ft_strlen(argv[i]);
		ft_strlcat(buf, argv[i], size + 1);
		++i;
		if (i < argc)
		{
			buf[size] = ' ';
			size += 1;
		}
	}

	init_tokenizer(&tokenizer, buf);
	lst = tokenize_all_tokens(&tokenizer);
	token.identifier = 1;
	token_count = 0;
	while (lst != NULL)
	{
		token = *((t_token *)lst->content);
 		printf("[%.*s]:%zi,%i\n", (int)token.length, token.text, token.length, token.identifier);
		lst = lst->next;
		++token_count;
	}
	printf("Total Token count:%i\n", token_count);
	// NOTE:
	// argmax = 2097152
	// is this values always same for all codam computers?
	// NOTE: Is this necessary or is ARG_MAX not to big for most or this system?
	return 0;
}
