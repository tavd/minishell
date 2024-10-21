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

#include "libft/bool.h"
#include "libft/libft.h"

#include <limits.h>
#include <unistd.h>

#include <stdlib.h>

// remove eventually
#include <stdio.h>
#include <string.h>

/*
*	An enum for more readable code. "ENV_VAR" is not an accurate name for '$',
*	but in the case of minishell it is exhaustive of the chars function. Right?
*/
// TODO: make it possible for heredoc to set a word as END delimiter...
enum e_identifiers
{
	END,
	WORD,
	SPACE = ' ',
	NEW_LINE = '\n',
	TAB = '\t',
	ENV_VAR = '$',
	SET_ENV_VAR = '=',
// WHAT IS it doing:
//	 x echo= ="hello = wi"
//	=hello = wi: command not found
	PIPE = '|',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	OPEN_BRACE = '{',
	CLOSE_BRACE = '}',

	// ... not sure about these yet
	HEREDOC_END,
};

struct s_tokenizer {
	char	*input;
};

typedef struct s_token {
	char			*text;
	ssize_t			length;
	enum e_identifiers	identifier;
}	t_token;

// NOTE: Whitespace should only be reduced while or after all subtitutions?
#define WHITE_SPACE_CHARS SPACE, TAB, NEW_LINE

const static char	WHITE_SPACE[4] = {
	WHITE_SPACE_CHARS, '\0'
};

# define SINGLE_TOKEN_CHARS SINGLE_QUOTE, DOUBLE_QUOTE, \
	OPEN_BRACE, CLOSE_BRACE, REDIRECT_IN, REDIRECT_OUT, \
	PIPE, ENV_VAR, SET_ENV_VAR

const static char	SINGLE_TOKENS[10] = {
	  SINGLE_TOKEN_CHARS, '\0'
};

// Maybe combining is too inflexible for some cases?
const static char	WORD_DELIMITERS[14] = {
	WHITE_SPACE_CHARS, SINGLE_TOKEN_CHARS, '\0'
};
	// SPACE, TAB, NEW_LINE,
	// SINGLE_QUOTE, DOUBLE_QUOTE, REDIRECT_IN, REDIRECT_OUT,
	// PIPE, SET_ENV, ENV_VAR, END

//=============================================================================

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
	if (strchr(SINGLE_TOKENS, token.identifier))
	{
		token.length += 1;
		tokenizer->input += 1;
		return (token);
	}
	token.identifier = WORD;
	while (strchr(WORD_DELIMITERS, str[token.length]) == NULL)
		++token.length;
	tokenizer->input += token.length;
	return (token);
}

void	free_data(void *data)
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
			ft_lstclear(&head, &free_data);
			return (NULL);
		}
		token = tokenize_one_token(tokenizer);
		*tok_ptr = token;
		new_node->content = (void *)tok_ptr;
		ft_lstadd_back(&head, new_node);
	}
	return (head);
}

void	expand_env_var(void *content)
{
	t_token	token;

	token = *((t_token *)content);
	if (token.identifier == ENV_VAR)
		printf("%.*s\n", (int)token.length, token.text);

}

// NOTE: WHY does this make it possible for indirect pointer to change head node?
typedef struct	s_linked_list {
	t_list	*head;
}	t_linked_list;

// Removes the single_quote tokens and
// Makes all the token identifiers in between single quotes words and removes.
bool	parse_single_quotes(t_linked_list *lst)
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

int	single_quote(t_list **node)
{
	static bool	in_single_quotes = false;
	t_token *token;
	
	token = (t_token *)(*node)->content;
	if (token->identifier == SINGLE_QUOTE)
	{
		next_node = (*node)->next;
		ft_lstdelone(*node, free_data);
		*node = next_node;
		in_single_quotes = !in_single_quotes;
	}
	return (in_single_quotes);
}

enum	e_errors
{
	UNCLOSED_QUOTE_ERROR,
};

// If there is a good way to handle errors we could also return ptr to place where
// error occured
int	parser_simple(t_linked_list *lst)
{
	char	*parsed_str;
	t_token	*token;

	parsed_str = "";
	if (parse_single_quotes(lst) == 1)
		return (UNCLOSED_QUOTE_ERROR);
	ft_lst_iter(lst->head, expand_env_var);

	//ft_lstiter(tokens, &expand_var); Enough ???
	return (0);
}

// NOTE: NOT GENERIC ENOUGH TO BE WORTH IT?
int	ft_lstiter_andor_modify(t_list **lst, int (*f)(t_list **))
{
	t_list	**list_item;
	int	fn_return;

	if (!lst || !f)
		return ;
	lst_item = lst;
	fn_return = 0;
	while (*lst_item != NULL)
	{
		fn_return = f(lst_item);
		lst_item = &(*lst_item)->next;
	}
	return (fn_return);
}


// NOTE : optoions is to  Tokenize once, get the count, then malloc for that count
int main(int argc, char **argv)
{
	struct s_tokenizer tokenizer;
	t_token		token;
	int		token_count;
	int	i;
	int	size;
	t_linked_list	lst;
	t_list	*lst_item;

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

	init_tokenizer(&tokenizer, buf);
	printf("unparsed: %s\n", buf);
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

	printf("parser:\n");
	return (0);
}
// argmax = 2097152
// is this values always same for all codam computers?
// NOTE: Is this necessary or is ARG_MAX not to big for most or this system?
