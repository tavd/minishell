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

struct tokenizer {
	char	*input;
};

enum e_identifier
{
	SPACE,
	ENV,
	EXIT_STATUS,

	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,

	END,
	HEREDOC_END,
};

typedef struct s_token {
	// TODO: make it possible for heredoc to set a word as END delimiter...
	enum e_identifier identifier;
	char	*text;
	ssize_t	length;
	bool	valid;
}	t_token;


const static	char	DELIMITERS[3] = {
	' ', '\n', '\0'
};

//=============================================================================

void	init_tokenizer(struct tokenizer *tokenizer, char *data)
{
	tokenizer->input = data;
}

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*str_buf;
	char		*token;
	size_t		len;

	if (str)
		str_buf = str;
	token = str_buf;
	len = 0;
	while (*str_buf && strchr(delimiters, *str_buf) == NULL) // NOTE: make ft_strchr
	{
		++str_buf;
		++len;
	}
	if (len == 0)
		return (NULL);
	else
		++str_buf;
	token[len] = '\0';
	return (token);
}

t_token	tokenize_one_token(struct tokenizer *tokenizer)
{
	t_token		token;
	char		*str;
	int		len;

	str = tokenizer->input;
	token.text = str;
	token.valid = true;
	token.text = ft_strtok(str ,DELIMITERS);

	token.length = strlen(token.text);
	if (strncmp(str, "$?", 2) == 0)
	{
		token.identifier = EXIT_STATUS;
		token.length = 1;
	}
	else
		token.length = len;
	tokenizer->input += token.length;
	return (token);
}

int main()
{
	char str[15] = "hello\nworld! ";
	char	*token;

	token = ft_strtok(str, DELIMITERS);

	token = ft_strtok(NULL, DELIMITERS);
	printf("%s", token);

	return 0;
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
