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
	UNEXPECTED_TOKEN,
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

char	*get_environment_variable_from_token(t_token *token)
{
	char	*variable;
	char	charswap_tmp;

	charswap_tmp = token->text[token->length];
	token->text[token->length] = '\0';
	variable = getenv(token->text);
	token->text[token->length] = charswap_tmp;
	return (variable);
}

// NOTE: This does not yet expand the exit status! It only marks it's place
void	expand_env_var(t_lst_embed **dollar_sign_node)
{
	t_token	*token;
	t_token	*next_token;

	token = (t_token *)(*dollar_sign_node);
	next_token = (t_token *)(*dollar_sign_node)->next;
	if (!next_token)
		token->identifier = WORD;
	else if (next_token->identifier == WORD)
	{
		token->text = get_environment_variable_from_token(next_token);
		if (token->text)
			token->length = ft_strlen(token->text); // TODO: find an overall safer design for token's that contain NULL as the string they point to? or nah...
		ft_sll_remove_node(&(*dollar_sign_node)->next, NULL);
	}
	else if (next_token->identifier == QUESTION_MARK)
	{
		token->identifier = SET_EXIT_STATUS;
		ft_sll_remove_node(&(*dollar_sign_node)->next, NULL);
	}
	else
		token->identifier = WORD;
}

void	remove_token(t_lst_embed **lst_token)
{
	ft_sll_remove_node((t_lst_embed **)lst_token, NULL);
}

/// find quote token, delete it , make all words between quote token WORD, 
bool	parse_double_quotes(t_lst_embed **lst)
{
	static bool	in_double_quotes = false;
	t_token		*token;

	while (*lst != NULL)
	{
		token = (t_token *)*lst;
		if (token->identifier == DOUBLE_QUOTE)
		{
			remove_token(lst);
			in_double_quotes = !in_double_quotes;
			continue;
		}
		else if (in_double_quotes)
{
			if (token->identifier == ENV_VAR)
				expand_env_var(lst);
		}
		else if (in_double_quotes && token->identifier == ENV_VAR)
			expand_env_var(lst);
		else if (in_double_quotes)
			token->identifier = WORD;
		lst = &(*lst)->next;
	}
	return (in_double_quotes);
}

// Make a function that ends either at END or when the second quote is found, then repeat this fn...
bool	parse_single_quotes(t_lst_embed **lst_token)
{
	static bool	in_single_quotes = false;
	t_token		*token;

	while (*lst_token != NULL)
	{
		token = (t_token *)*lst_token;
		if (token->identifier == SINGLE_QUOTE)
		{
			remove_token(lst_token);
			in_single_quotes = !in_single_quotes;
			continue;
		}
		else if (in_single_quotes)
			token->identifier = WORD;
		lst_token = &(*lst_token)->next;
	}
	return (in_single_quotes);
}

int	lst_iter(t_lst_embed **lst, int	(*func_ptr)(t_lst_embed **lst_node, int fn_return))
{
	int	fn_return;

	fn_return = 0;
	if (!lst)
		return (-1);
	while (*lst != NULL)
	{
		fn_return = func_ptr(lst, fn_return);
		lst = &(*lst)->next;
	}
	return (fn_return);
}

// int	single_quotes(t_lst_embed **lst_node, int in_single_quotes)
// {
// 	t_token	*token;
//
// 	token = (t_token *)*lst_node;
// 	if (token->identifier == SINGLE_QUOTE)
// 	{
// 		in_single_quotes = !in_single_quotes; //...
// 		ft_sll_remove_node(lst_node, NULL);
// 	}
// 	else if (in_single_quotes == true)
// 		token->identifier = WORD;
// 	return (in_single_quotes);
// }

// TODO: Make tokenizer do this... (maybe, eventually)
void	construct_heredoc_and_append_tokens(t_lst_embed **lst)
{
	t_token	*token;
	t_token	*next_token;

	//lst_embed	**redirect_in;
	// redirect_in = ft_lstfind(lst, has_identifier, (void *)REDIRECT_IN);
	// redirect_out = ft_lstfind(lst, has_identifier, (void *)REDIRECT_OUT);
	while (*lst && (*lst)->next)
	{
		
		token = (t_token *)*lst;
		next_token = (t_token *)(*lst)->next;
		if (token->identifier == REDIRECT_IN && \
			next_token->identifier == REDIRECT_IN)
		{
			token->length = 2;
			token->identifier = HEREDOC_MODE;
			ft_sll_remove_node(&(*lst)->next, NULL);
		}
		else if (token->identifier == REDIRECT_OUT && \
			next_token->identifier == REDIRECT_OUT)
		{
			token->length = 2;
			token->identifier = APPEND_MODE;
			ft_sll_remove_node(&(*lst)->next, NULL);
		}
		lst = &(*lst)->next;
	}
}

//					:: is this better/ good enough??
// void	construct(t_token **lst)
// {
// 	t_token *token;
//
// 	while (*lst && (*lst)->next)
// 	{
// 		token = *lst;
// 		if (token->identifier == REDIRECT_OUT && \
// 			token->next->identifier == REDIRECT_OUT)
// 		{
// 			ft_sll_remove_node((t_lst_embed *)next_token, NULL);
// 			token->identifier = HEREDOC_DEIM;
// 		}
// 		else if (token->identifier == REDIRECT_OUT && \
// 			token->next->identifier == REDIRECT_OUT)
// 		{
// 			ft_sll_remove_node((t_lst_embed *)next_token, NULL);
// 			token->identifier = HEREDOC_DEIM;
// 		}
// 	}
// }

t_lst_embed	**ft_lstfind(t_lst_embed **lst,
	int (*compare_fn)(t_lst_embed *lst_node, void *target), void *target)
{
	while (*lst != NULL)
	{
		if (compare_fn(*lst, target))
			return (lst);
		lst = &(*lst)->next;
	}
	return (NULL);
}

int	has_identifier(t_lst_embed *node, void *target_identifier)
{
	t_token	*token;

	token = (t_token *)node;
	if (token->identifier == (intptr_t)target_identifier)
		return (true);
	else
		return (false);
}

t_token *token_after_space(t_lst_embed *node)
{
	t_token	*token;

	if (!node->next || !node->next->next)
		return (NULL);
	token = (t_token *)node->next;
	if (token->identifier != SPACE)
		return (NULL);
	token = (t_token *)node->next->next;
	 return (token);
}

void	*quote_removal(t_lst_embed **node)
{

	return (node);
}

int	parse_heredoc_delimiter(t_lst_embed **lst)
{
	t_token		*next_token;

	lst = ft_lstfind(lst, has_identifier, (void *)HEREDOC_MODE);
	while (lst && *lst)
	{
		next_token = token_after_space(*lst);
		if (!next_token)
			return (UNEXPECTED_TOKEN);
		else if (next_token->identifier == WORD)
			next_token->identifier = HEREDOC_UNQUOTED_WORD;
		else if (next_token->identifier == SINGLE_QUOTE)
		{
			quote_removal(&(*lst)->next->next);
			///....
			return (UNEXPECTED_TOKEN);
		}
		else if (next_token->identifier == DOUBLE_QUOTE)
		{

		}
		else
			return (UNEXPECTED_TOKEN);
		lst = ft_lstfind(&(*lst)->next, has_identifier, (void *)HEREDOC_MODE);
	}
	return (OK);
}

enum e_parsing_errors	parser_simple(t_token **lst)
{
//	int	error_status;

	construct_heredoc_and_append_tokens((t_lst_embed **)lst); // Should be done by tokenizer in future
	if (parse_heredoc_delimiter((t_lst_embed **)lst))
		return (UNEXPECTED_TOKEN);
	if (parse_double_quotes((t_lst_embed **)lst))
		return (UNCLOSED_DOUBLE_QUOTES);
	if (parse_single_quotes((t_lst_embed **)lst))
		return (UNCLOSED_SINGLE_QUOTES);

	

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

	//buf = simple_word_unifier(argc, argv);
	if (argc < 2)
		return 0;

	buf = ft_strdup(argv[1]);
	init_tokenizer(&tokenizer, buf);
	printf("unparsed: %s\n", buf);
	printf("after parsing pass: \n");
	lst = tokenize_all_tokens(&tokenizer);
	if (parser_simple(&lst))
		printf("ERROR\n");

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
