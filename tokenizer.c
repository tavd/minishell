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

void	init_tokenizer(struct tokenizer *tokenizer, char *data)
{
	tokenizer->input = data;
}

const static	char	delims[3] = {
	' ', '\0', '\n'
};

// NOTE:
// all tokens of length 1 are identifiers...

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*str_buf;
	char		*token;
	size_t		len;

	if (str)
		str_buf = str;
	token = str_buf;
	len = 0;
	while (*str_buf && strchr(delimiters, *str_buf) == NULL)
	{
		++str_buf;
		++len;
	}
	token[len] = '\0';
	return (token);
}

int main()
{
	char str[14] = "hello\nworld! ";
	char	*token;

	token = ft_strtok(str, delims);
	printf("%s", token);
	printf("%s", str);
	
	return 0;
}

//
// t_token	tokenize_one_token(struct tokenizer *tokenizer)
// {
// 	t_token		token;
// 	char		*string;
// 	int		len;
//
// 	string = tokenizer->input;
// 	token.literal_value = string;
// 	token.valid = true;
// 	len = 0;
// 	while (*string && !strchr(delimiters, *string))
// 	{
// 		++string;
// 		++len;
// 	}
// 	if (len == 0)
// 	{
// 		token.literal_value = 0;
// 		token.identifier = *string;
// 		token.length = 1;
// 	}
// 	else if (strncmp(string, "$?", 2) == 0)
// 	{
// 		token.identifier = EXIT_STATUS;
// 		token.length = 1;
// 	}
// 	else
// 		token.length = len;
// 	tokenizer->input += token.length;
// 	return (token);
// }
//
// int main()
// {
// 	struct tokenizer tokenizer;
//
// 	char *str = "test .... string";
// 	t_token		token;
//
// 	init_tokenizer(&tokenizer, str);
//
// 	printf("untokenized string: %s\n", tokenizer.input);
//
// 	token = tokenize_one_token(&tokenizer);
// 	printf("%zu\n", token.length);
//
// 	printf("%.*s\n", (int)token.length, token.literal_value);
// 	
// 	printf("%s\n", tokenizer.input);
//
// 	printf("%.*s\n", (int)token.length, token.literal_value);
//
// 	token = tokenize_one_token(&tokenizer);
//
// 	token = tokenize_one_token(&tokenizer);
//
// 	printf("%.*s\n", (int)token.length, token.literal_value);
// 	printf("%i", token.identifier);
// 	
// 	printf("%s\n", tokenizer.input);
//
//
//
//
//
// 	return 0;
// }
