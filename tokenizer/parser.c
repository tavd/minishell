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
enum	e_parsing_errors
{
	UNCLOSED_QUOTE_ERROR,
};

enum e_parser_context
{
	EXIT_STATUS = 256,
	HEREDOC_EOF = 257,

};
// ================================================================================

// cleanly remove node form list
void	ft_lst_remove(t_list **node_to_remove, void (*del)(void *content))
{
	t_list	*next_node;

	if (!node_to_remove)
		return ;
	next_node = (*node_to_remove)->next;
	ft_lstdelone(*node_to_remove, del);
	*node_to_remove = next_node;
}

void	free_data(void *data)
{
	free(data);
}

void	expand_env_var(t_list **current_node)
{
	t_token	*token;
	t_token	*next_token;
	char	temp_for_swap;
	char	*variable_name;

	if (!(*current_node)->next)
		return ;
	token = (t_token *)(*current_node)->content;
	next_token = (t_token *)(*current_node)->next->content;
	if (next_token->identifier == QUESTION_MARK)
	{
		token->identifier = PARSER_EXIT_STATUS; // TODO: how to identify EXIT_STATUS_LEN in next step?
		ft_lst_remove(&(*current_node)->next, free_data); // NOTE: This can not be next_node, WHY?
	}
	else if (next_token->identifier == WORD)
	{
		temp_for_swap = next_token->text[next_token->length];
		next_token->text[next_token->length] = '\0';
		variable_name = next_token->text;
		token->text = getenv(variable_name);
		token->length = ft_strlen(token->text); // BUG: NULL safe strlen needed
		next_token->text[next_token->length] = temp_for_swap;
		ft_lst_remove(&(*current_node)->next, free_data); // NOTE: This can not be next_node, WHY?
	}
}

bool	double_q_parse(t_list **current_node)
{
	static bool	in_double_quotes = false;
	t_token		*token;

	while (*current_node != NULL)
	{
		token = (t_token *)(*current_node)->content;
		if (token->identifier == DOUBLE_QUOTE)
		{
			ft_lst_remove(current_node, free_data);
			in_double_quotes = !in_double_quotes;
			continue;
		}
		else if (in_double_quotes && token->identifier == ENV_VAR)
			expand_env_var(current_node);
		else if (in_double_quotes)
			token->identifier = WORD;
		current_node = &(*current_node)->next;
	}
	return (in_double_quotes);
}

// BUG: why did this not work with **lst
bool	single_q_parser(t_list **current_node)
{
	static bool	in_single_quotes = false;
	t_token		*token;

	while (*current_node != NULL)
	{
		token = (t_token *)(*current_node)->content;
		if (token->identifier == SINGLE_QUOTE)
		{
			ft_lst_remove(current_node, free_data);
			in_single_quotes = !in_single_quotes;
			continue;
		}
		else if (in_single_quotes)
			token->identifier = WORD;
		current_node = &(*current_node)->next;
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
		if (*lst_item)
			lst_item = &(*lst_item)->next;
	}
	return (fn_return);
}

ssize_t	ft_secure_strlen(char *str)
{
	if (!str)
		return (-1);
	else
		return ((ssize_t)ft_strlen(str));
}


int	parse_single_quotes(t_list **current_node)
{
	static bool	in_single_quotes = false;
	t_token *token;
	
	token = (t_token *)(*current_node)->content;
	if (token->identifier == SINGLE_QUOTE)
	{
		ft_lst_remove(current_node, free_data);
		in_single_quotes = !in_single_quotes;
	}
	else if (in_single_quotes)
		token->identifier = WORD;
	return (in_single_quotes);
}

// NOTE: We expand env_vars in this order: Double quotes, single quotes, no quotes
int	parser_simple(t_list **lst)
{
	char	*parsed_str;
	t_token	*token;

	parsed_str = "";
	double_q_parse(lst);
	single_q_parser(lst);

	//ft_lstiter_mod(lst, &prase_double_quotes)
	// if (ft_lstiter_mod(lst, &parse_single_quotes))
	// 	return (UNCLOSED_QUOTE_ERROR);
	//ft_lstiter_mod(lst, &expand_env_var);
		

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
	t_list	*lst_item;
	char	*buf;
	t_list	*lst;
	//t_linked_list	lst;

	buf = simple_word_unifier(argc, argv);
	init_tokenizer(&tokenizer, buf);
	printf("unparsed: %s\n", buf);
	printf("after parsing pass: \n");
	lst = tokenize_all_tokens(&tokenizer);

	parser_simple(&lst);

	token.identifier = 1;
	token_count = 0;
	lst_item = lst;
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
