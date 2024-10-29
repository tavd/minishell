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
	token.identifier = (enum e_token_identifier)*str;
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

// malloc's space for token lst struct and initializes it IF a valid ptr is psdlfkjdffassed in
struct s_token	*lst_new_token(struct s_token token)
{
	struct s_token	*token_mem;

	token_mem = (struct s_token *)malloc(sizeof(struct s_token));
	if (!token_mem)
		return (NULL);
	*token_mem = token;
	// Should this be done or poses risk of losing important data?
	// token_mem->list.prev = NULL;
	// token_mem->list.next = NULL;
	return (token_mem);
}


// embed ...
void	ft_sll_addback(t_lst_embed **head, t_lst_embed *new_node)
{
	t_lst_embed	*current;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	new_node->next = NULL;
	new_node->prev = NULL;
}

// #include <stdio.h>
// int	main()
// {
//
// 	t_lst_embed	*head;
// 	t_token		*new;
//
// 	head = NULL;
//
// 	new = lst_new_token((struct s_token){.identifier = 1});
// 	ft_sll_addback(&head, &new->lst_info);
// 	new = lst_new_token((struct s_token){.identifier = 2});
// 	ft_sll_addback(&head, &new->lst_info);
//
// 	t_token	*tok = (t_token *)head;
// 	
// 	tok = (t_token *)tok->lst_info.next;
//
// 	printf("%i\n", tok->identifier);
//
// 	return 0;
// }

// NOTE:  since the t_lst_embed struct is the first member of
// the struct t_token, it can be savely casted to a t_token.
t_token	*tokenize_all_tokens(struct s_tokenizer *tokenizer)
{
	t_lst_embed	*head;
	t_token		token;
	t_token		*new_token;

	head = NULL;
	token.identifier = 1;
	while (token.identifier != END)
	{
		new_token = (t_token *)malloc(sizeof(t_token)); 
		if (!new_token)
		{
			//ft_lstclear(&head, &free_token);
			return (NULL);
		}
		token = tokenize_one_token(tokenizer);
		token.lst_info.prev = NULL;
		token.lst_info.next = NULL;
		*new_token = token;// BUG:Does this copy all of the data correctly?
		ft_sll_addback(&head, &new_token->lst_info);
	}
	return ((t_token *)head);
}


