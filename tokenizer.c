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

#include <stdint.h>
#include <stdbool.h>

// remove eventually
#include <stdio.h>
#include <string.h>

// TODO: make it possible for heredoc to set a word as END delimiter...
enum e_identifiers
{
	SPACE = ' ',
	ENV = '$',
	EXIT_STATUS = '?',
	PIPE = '|',

	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	REDIRECT_APPEND = 'a',

	WORD,
	NEW_LINE = '\n',
	END = '\0',
	HEREDOC_END,
};

const static	char	DELIMITERS[3] = {
	' ', '\n', '\0'
};

typedef struct s_token {
	char			*text;
	ssize_t			length;
	enum e_identifiers	identifier;
}	t_token;


struct s_tokenizer {
	char	*input;
};

//=============================================================================

// NOTE: makes a shallow copy...
void	init_tokenizer(struct s_tokenizer *tokenizer, char *data)
{
	tokenizer->input = data;
}

t_token	tokenize_one_token(struct s_tokenizer *tokenizer)
{
	char	*str;
	t_token	token;

	str = tokenizer->input;
	token.text = NULL;
	token.identifier = END;
	token.length = 0;
	while (*str && strchr(DELIMITERS, *str) != NULL)
		++str;
	if (*str == '\0')
		return (token);
	token.text = str;
	while (*str && strchr(DELIMITERS, *str) == NULL)
	{
		++str;
		++token.length;
	}
	if (token.length == 0 && *str == '\0')
		return (token);
	else if (token.length == 0)
	{
		token.text = 0;
		token.identifier = *str;
		token.length = 1;
	}
	else
		token.identifier = WORD;
	tokenizer->input = str;
	return (token);
}

int main()
{
	struct s_tokenizer tokenizer;
	char	*str = strdup(" \n\nhello\n world!");
	t_token		token;

	init_tokenizer(&tokenizer, str);
	printf("untokenized str: %s\n", tokenizer.input);

	token.text = (char *)1;
	while (token.text)
	{
		token = tokenize_one_token(&tokenizer);
		if (token.text)
			printf("[%.*s]", (int)token.length, token.text);
	}
	printf("\noriginal string:%s", str);
}
