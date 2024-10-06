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

typedef struct s_token {

	union {
		char	*literal_value;
		uint8_t	identifier;
	};
	ssize_t	length;
	bool	valid;
}	t_token;

void	init_tokenizer(struct tokenizer *tokenizer, char *data)
{
	tokenizer->input = data;
}

const static	char	delimiters[3] = {
	' ', '\0', '\n'
};

enum e_identifiers
{
	END = 0,
	SPACE = ' '
};

t_token	tokenize_one_at_a_time(struct tokenizer *tokenizer)
{
	t_token		token;
	char		*string;
	int		len;

	string = tokenizer->input;
	token.literal_value = string;
	token.valid = true;
	while (*string && !strchr(delimiters, *string))
	{
		++string;
		++len;
	}
	if (len == 0)
	{
		token.literal_value = 0;
		token.identifier = (enum e_identifiers)*string;
		token.length = 1;
	}
	else
		token.length = len;
	tokenizer->input += token.length;
	return (token);
}

int main()
{
	struct tokenizer tokenizer;

	char *str = "test .... string";
	t_token		token;

	init_tokenizer(&tokenizer, str);

	printf("untokenized string: %s\n", tokenizer.input);

	token = tokenize_one_at_a_time(&tokenizer);
	printf("%zu\n", token.length);

	printf("%.*s\n", (int)token.length, token.literal_value);
	
	printf("%s\n", tokenizer.input);

	printf("%.*s\n", (int)token.length, token.literal_value);

	token = tokenize_one_at_a_time(&tokenizer);
	//token = tokenize_one_at_a_time(&tokenizer);
	//printf("%i", token.identifier);




	return 0;
}
