/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:06:29 by mzwart            #+#    #+#             */
/*   Updated: 2024/10/24 19:07:05 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>

// remove eventually
#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include "tokenizer.h"
//#include "libft/string.h"
#include "libft/libft.h"

// NOTE: WHY does this make it possible for indirect pointer to change head node?
typedef struct	s_linked_list {
	t_list	*head;
}	t_linked_list;

// If there is a good way to handle errors we could also return ptr to place where
// error occured
enum	e_errors
{
	UNCLOSED_QUOTE_ERROR,
};

// ================================================================================

void	expand_env_var(void *content)
{
	t_token	token;

	token = *((t_token *)content);
	if (token.identifier == ENV_VAR)
		printf("%.*s\n", (int)token.length, token.text);

}

void	free_data(void *data)
{
	free(data);
}

// Removes the single_quote tokens and
// Makes all the token identifiers in between single quotes a WORD and removes '.
bool	single_q_parser(t_linked_list *lst)
{
	static bool	in_single_quotes = false;
	t_list		**lst_address;
	t_list		*next_node;
	t_token		*token;

	lst_address = &lst->head;
	while (*lst_address != NULL)
	{
		token = (t_token *)(*lst_address)->content;
		if (token->identifier == SINGLE_QUOTE)
		{
			next_node = (*lst_address)->next;
			ft_lstdelone(*lst_address, free_data);
			*lst_address = next_node;
			in_single_quotes = !in_single_quotes;
			continue;
		}
		else if (in_single_quotes)
			token->identifier = WORD;
		lst_address = &(*lst_address)->next;
	}
	return (in_single_quotes);
}

// iterates over linked list and applies a fn to every linked list node.
// the fn gets passed an indirect pointer of a node to allow for easy modification
// of the linked list itself. (it makes it so you dont need a ptr to previous node ).
int	ft_lstiter_mod(t_list **lst, int (*mod_fn)(t_list **))
{
	t_list	**lst_item;
	int	fn_return;

	if (!lst || !mod_fn)
		return 0;
	fn_return = 0;
	lst_item = lst;
	while (*lst_item != NULL)
	{
		fn_return = mod_fn(lst_item);
		lst_item = &(*lst_item)->next;
	}
	return (fn_return);
}

int	parse_single_quotes(t_list **current_node)
{
	static bool	in_single_quotes = false;
	t_token *token;
	t_list	*next_node;
	
	token = (t_token *)(*current_node)->content;
	if (token->identifier == SINGLE_QUOTE)
	{
		next_node = (*current_node)->next;
		ft_lstdelone(*current_node, free_data);
		*current_node = next_node;
		in_single_quotes = !in_single_quotes;
	}
	else if (in_single_quotes)
		token->identifier = WORD;
	return (in_single_quotes);
}

int	parser_simple(t_linked_list *lst)
{
	char	*parsed_str;
	t_token	*token;

	parsed_str = "";
	if (ft_lstiter_mod(&(lst->head), &parse_single_quotes) == 1)
		return (UNCLOSED_QUOTE_ERROR);
	ft_lstiter(lst->head, expand_env_var);

	return (0);
}

char	*simple_word_unifier(int argc, char **argv)
{
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
	return (buf);
}

// NOTE : optoions is to  Tokenize once, get the count, then malloc for that count
int main(int argc, char **argv)
{
	struct s_tokenizer tokenizer;
	t_token		token;
	int		token_count;
	t_linked_list	lst;
	t_list	*lst_item;
	char	*buf;

	buf = simple_word_unifier(argc, argv);
	init_tokenizer(&tokenizer, buf);
	printf("unparsed: %s\n", buf);
	printf("after parsing pass: \n");
	lst.head = tokenize_all_tokens(&tokenizer);
	parser_simple(&lst);

	token.identifier = 1;
	token_count = 0;
	lst_item = lst.head;
	while (lst_item != NULL)
	{
		token = *((t_token *)lst_item->content);
 		printf("[%.*s]:%zi,%i\n", (int)token.length, token.text, token.length, token.identifier);
		lst_item = lst_item->next;
		++token_count;
	}
	printf("Total Token count:%i\n", token_count);

	return (0);
}
// argmax = 2097152
// is this values always same for all codam computers?
// NOTE: Is this necessary or is ARG_MAX not to big for most or this system?
