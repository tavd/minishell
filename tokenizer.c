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
// ASCII to identifier map...

typedef struct s_token {
	char			*text;
	ssize_t			length;
	enum e_identifiers	identifier;
}	t_token;

struct s_tokenizer {
	char	*input;
};

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

// This function returns current token and length and needs to 
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
		tokenizer->input += 1;
		return (token);
	}
	token.identifier = WORD;
	while (strchr(WORD_DELIMITERS, str[token.length]) == NULL)
		++token.length;
	tokenizer->input += token.length;
	return (token);
}

int main()
{
	struct s_tokenizer tokenizer;
	char	*str = "hel $lo_world$H";
	t_token		token;

	init_tokenizer(&tokenizer, str);
	printf("untokenized str:%s\n", tokenizer.input);

	token.identifier = 1;
	while (tokenizer.input != NULL && token.identifier != END)
	{
		token = tokenize_one_token(&tokenizer);
		printf("[%.*s]:%zi,%i", (int)token.length, token.text, token.length, token.identifier);
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
