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
	SET_ENV = '=',
	ENV_VAR = '$',
	EXIT_STATUS = '?',
	PIPE = '|',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	REDIRECT_APPEND = 'a',

	WORD,
	SINGLE_QUOTE = 39,
	DOUBLE_QUOTE = 34,

	HEREDOC_END,

	NEW_LINE = '\n',
	END = '\0',
};

// NOTE: Newline?
const static	char	NORMAL_DELIMS[3] = {
	SPACE, NEW_LINE, END
};

const static char	SINGLE_QUOTE_DELIMS[2] = {
	SINGLE_QUOTE, END

};

const static char	DOUBLE_QUOTE_DELIMS[3] = {
	ENV_VAR, DOUBLE_QUOTE, END
};


const static char	*DELIMITERS[3] = {
	NORMAL_DELIMS, SINGLE_QUOTE_DELIMS, DOUBLE_QUOTE_DELIMS
};

// NOTE: is {} part of subject ???
const static char	ENV_VAR_DELIMS[3] = {
	ENV_VAR, SPACE, END

};

typedef struct s_token {
	char			*text;
	ssize_t			length;
	enum e_identifiers	identifier;
}	t_token;

struct s_tokenizer {
	char	*input;
};

enum e_map_quotes
{
	NONE = 0,
	SINGLE = 1,
	DOUBLE = 2,
};

//=============================================================================

// TODO: makes a shallow copy...can this go wrong?
void	init_tokenizer(struct s_tokenizer *tokenizer, char *data)
{
	tokenizer->input = data;
}

t_token	tokenize_one_token(struct s_tokenizer *tokenizer)
{
	char	*str;
	t_token	token;
	static	int	quote_state;
arser  (1)!✘ # echo "hello"
	str = tokenizer->input;
	token.text = NULL;
	token.identifier = END;
	token.length = 0;

	// NOTE: THIS doesn't work, should stop at quotes
	while (*str && quote_state == 0 && strchr(DELIMITERS[quote_state], *str) != NULL) // make ft
		++str;
	if (*str == '\0')
		return (token);
	token.text = str;
	while (*str && strchr(DELIMITERS[quote_state], *str) == NULL)
	{
		++str;
		++token.length;
	}
	if (token.length == 0 && *str == '\0')
		return (token);
	else if (token.length == 0 && *str == SINGLE_QUOTE || *str == DOUBLE_QUOTE)
	{
		// TODO: map quote char to quote state ...

	}
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


// int main()
// {
// 	struct tokenizer tokenizer;
//
// 	char *str = "test .... str";
// 	t_token		token;
//
// 	init_tokenizer(&tokenizer, str);
//
// 	printf("untokenized str: %s\n", tokenizer.input);
//
// 	token = tokenize_one_token(&tokenizer);
// 	printf("%zu\n", token.length);
//
// 	printf("%.*s\n", (int)token.length, token.text);
// 	
// 	printf("%s\n", tokenizer.input);
//
// 	printf("%.*s\n", (int)token.length, token.text);
//
// 	token = tokenize_one_token(&tokenizer);
//
// 	token = tokenize_one_token(&tokenizer);
//
// 	printf("%.*s\n", (int)token.length, token.text);
// 	printf("%i", token.identifier);
// 	
// 	printf("%s\n", tokenizer.input);
//
// 	return 0;
// }
//
// NOTE:
// all tokens of length 1 are identifiers...
//
