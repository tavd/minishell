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
enum	e_errors
{
	UNCLOSED_QUOTE_ERROR,
	MALLOC_FAIL_ENV_EXPANSION,
};
// ================================================================================

void	free_data(void *data)
{
	free(data);
}

// BUG: why did this not work with **lst
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

ssize_t	ft_secure_strlen(char *str)
{
	if (!str)
		return (-1);
	else
		return ((ssize_t)ft_strlen(str));
}

char	*ft_strndup(char *str, size_t len)
{
	return (NULL);

}

	//NOTE: maybe add more context to list_item for whether a var is expanded
int	expand_env_var(t_list **current_node) // How to acces exit_status?
{
	t_token	*token;
	t_token	*next_token;
	t_list	*next_node;
	char	*variable_name;
	char	temp_for_swap;

	next_node = (*current_node)->next;
	token = (t_token *)(*current_node)->content;
	if (token->identifier)
	if (token->identifier == ENV_VAR)
	{
		token->text = NULL;
		if (!next_node)
			return (0);
		next_token = next_node->content;
		if (next_token->identifier == QUESTION_MARK)
		{
			token->text = "exit_status";// ft_itoa(exit_status); // exit_statues
			token->length = ft_strlen(token->text);
		}
		else if (next_token->identifier == WORD)
		{
			temp_for_swap = next_token->text[next_token->length];
			next_token->text[next_token->length] = '\0';
			token->text = getenv(next_token->text);
			next_token->text[next_token->length] = temp_for_swap;
			//token->length = ft_strlen(token->text);
		}
	}
	return (0);
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


int	parser_simple(t_list **lst)
{
	char	*parsed_str;
	t_token	*token;

	parsed_str = "";
	if (ft_lstiter_mod(lst, &parse_single_quotes))
		return (UNCLOSED_QUOTE_ERROR);
	if (ft_lstiter_mod(lst, &expand_env_var))
		return (MALLOC_FAIL_ENV_EXPANSION);

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
