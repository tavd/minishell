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
	OK,
	UNCLOSED_SINGLE_QUOTES,
	UNCLOSED_DOUBLE_QUOTES,
};

enum e_parser_context
{
	EXIT_STATUS = 256,
	HEREDOC_EOF = 257,

};
// ================================================================================

// Free's the node and switches its address out for address of the next node
// Returns if no current node.
void	ft_sll_remove_node(t_lst_embed **node_to_remove,
	void (*free_content_fn)(void *content_after_lst_embed))
{
	t_lst_embed	*next_node;
	
	if (node_to_remove == NULL || *node_to_remove == NULL)
		return ;
	next_node = (*node_to_remove)->next;
	if (free_content_fn)
		free_content_fn((void *)*node_to_remove);
	free(*node_to_remove);
	*node_to_remove = next_node;
}
	//content = (void *)*node_to_remove; // + sizeof(t_lst_embed);

ssize_t	ft_secure_strlen(char *str)
{
	if (!str)
		return (-1);
	else
		return ((ssize_t)ft_strlen(str));
}

// NOTE: This does not yet expand the exit status! It only marks it's place
void	expand_env_var(t_lst_embed **env_var_node)
{
	t_token	*token;
	t_token	*next_token;
	char	*variable_name;
	char	charswap_tmp;

	token = (t_token *)(*env_var_node);
	next_token = (t_token *)(*env_var_node)->next;
	// if (next_token == NULL || 
	// 	(next_token->identifier != WORD && next_token->identifier != QUESTION_MARK))
	if (next_token && next_token->identifier == WORD)
	{
		charswap_tmp = next_token->text[next_token->length];
		next_token->text[next_token->length] = '\0';
		variable_name = next_token->text;
		token->text = getenv(variable_name);
		if (token->text)
			token->length = ft_strlen(token->text);
		next_token->text[next_token->length] = charswap_tmp;
		ft_sll_remove_node(&(*env_var_node)->next, NULL);
	}
	else if (next_token && next_token->identifier == QUESTION_MARK)
	{
		token->identifier = SET_EXIT_STATUS;
		ft_sll_remove_node(&(*env_var_node)->next, NULL);
	}
	else
		token->identifier = WORD;
}

bool	parse_double_quotes(t_lst_embed **lst)
{
	static bool	in_double_quotes = false;
	t_token		*token;

	while (*lst != NULL)
	{
		token = (t_token *)*lst;
		if (token->identifier == DOUBLE_QUOTE)
		{
			ft_sll_remove_node(lst, NULL);
			in_double_quotes = !in_double_quotes;
			continue;
		}
		else if (in_double_quotes && token->identifier == ENV_VAR)
			expand_env_var(lst);
		else if (in_double_quotes)
			token->identifier = WORD;
		lst = &(*lst)->next;
	}
	return (in_double_quotes);
}

bool	parse_single_quotes(t_lst_embed **lst)
{
	static bool	in_single_quotes = false;
	t_token		*token;

	while (*lst != NULL)
	{
		token = (t_token *)*lst;
		if (token->identifier == SINGLE_QUOTE)
		{
			ft_sll_remove_node(lst, NULL);
			in_single_quotes = !in_single_quotes;
			continue;
		}
		else if (in_single_quotes)
			token->identifier = WORD;
		lst = &(*lst)->next;
	}
	return (in_single_quotes);
}

void	construct_heredoc_and_append_tokens(t_lst_embed **lst)
{
	t_token	*token;
	t_token	*next_token;

	while (*lst && (*lst)->next)
	{
		token = (t_token *)*lst;
		next_token = (t_token *)(*lst)->next;
		if (token->identifier == REDIRECT_IN && \
			next_token->identifier == REDIRECT_IN)
		{
			token->identifier = HEREDOC_DELIM;
			ft_sll_remove_node(&(*lst)->next, NULL);
		}
		else if (token->identifier == REDIRECT_OUT && \
			next_token->identifier == REDIRECT_OUT)
		{
			token->identifier = APPEND_MODE;
			ft_sll_remove_node(&(*lst)->next, NULL);
		}
		lst = &(*lst)->next;
	}
}

void	construct(t_token **lst)
{
	t_token *token;

	while (*lst)
	{
		token = *lst;
		if (!token->next
		if (token->next && token->identifier == REDIRECT_OUT && \
			token->next->identifier == REDIRECT_OUT)
		{
			ft_sll_remove_node((t_lst_embed *)next_token, NULL);
			token->identifier = HEREDOC_DEIM;
		}
		else if (token->next && token->identifier == REDIRECT_OUT && \
			token->next->identifier == REDIRECT_OUT)
		{
			ft_sll_remove_node((t_lst_embed *)next_token, NULL);
			token->identifier = HEREDOC_DEIM;
		}
	}
}

enum e_parsing_errors	parser_simple(t_token **lst)
{
	// char	*parsed_str;
	//
	// parsed_str = "";
	//parse_double_quotes(lst);
	pre_parse((t_lst_embed **)lst)

		
	if (parse_double_quotes((t_lst_embed **)lst))
		return (UNCLOSED_SINGLE_QUOTES);
	if (parse_single_quotes((t_lst_embed **)lst))
		return (UNCLOSED_DOUBLE_QUOTES);


	// if (ft_lstiter_mod(lst, &parse_single_quotes))
	// 	return (UNCLOSED_QUOTE_ERROR);
	//ft_lstiter_mod(lst, &expand_env_var);
	
	return (OK);
}

// char	**tokens_to_str_array(struct s_lst_embed *head)
// {
// 	t_lst_embed	current;
// 	t_token		*token;
// 	char	**argv;
// 	
// 	current = head;
// 	while (current != NULL)
// 	{
// 		
//
// 		current = current->next;
// 	}
//
// 	return (argv);
// }


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
	char	*buf;
	struct s_tokenizer tokenizer;
	t_token	*lst;
	t_token	*lst_token;
	int		token_count;
	t_token		token;
	//t_linked_list	lst;

	buf = simple_word_unifier(argc, argv);
	init_tokenizer(&tokenizer, buf);
	printf("unparsed: %s\n", buf);
	printf("after parsing pass: \n");
	lst = tokenize_all_tokens(&tokenizer);

	parser_simple(&lst);
	//ft_lstclear(&lst, NULL);


	token.identifier = 1;
	token_count = 0;
	lst_token = lst;
	while (lst_token != NULL)
	{
		token = *(lst_token);
 		printf("[%.*s]:%zi,%i\n", (int)token.length, token.text, token.length, token.identifier);
		lst_token = (t_token *)lst_token->lst_info.next;
		++token_count;
	}
	printf("Total Token count:%i\n", token_count);

	return (0);
}
// argmax = 2097152
// is this values always same for all codam computers?
// NOTE: Is this necessary or is ARG_MAX not to big for most or this system?
