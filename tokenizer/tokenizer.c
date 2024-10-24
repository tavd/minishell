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

#include <stdlib.h>
#include "tokenizer.h"

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
	while (ft_strchr(WHITE_SPACE, str[token.length]))
		++token.length;
	if (str[token.length] == END || token.length > 0)
	{
		tokenizer->input += token.length;
		return (token);
	}
	if (ft_strchr(SINGLE_TOKENS, token.identifier))
	{
		token.length += 1;
		tokenizer->input += 1;
		return (token);
	}
	token.identifier = WORD;
	while (ft_strchr(WORD_DELIMITERS, str[token.length]) == NULL)
		++token.length;
	tokenizer->input += token.length;
	return (token);
}

void	free_token(void *data)
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
			ft_lstclear(&head, &free_token);
			return (NULL);
		}
		token = tokenize_one_token(tokenizer);
		*tok_ptr = token;
		new_node->content = (void *)tok_ptr;
		ft_lstadd_back(&head, new_node);
	}
	return (head);
}
