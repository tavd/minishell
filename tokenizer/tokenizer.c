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

#include "tokenizer.h"

#include <assert.h>

t_tokenizer	create_tokenizer(const char *start_input, const char *end_input)
{
	return (t_tokenizer)
	{
		.begin = (char *)start_input,
		.end = (char *)end_input,
		.cur = 0,
	};
}

t_toklen	is_nullterm(const char *str, t_symbol_id id)
{
	if (ft_strncmp(str, SYMBOL_TABLE[id][SYMBOL], 1) == 0)
		return (0);
	return (-1);
}

// TODO: merge is_nullterm into fn below
t_toklen	symbol(const char *str, t_symbol_id id)
{
	const size_t	symbol_len = ft_strlen(SYMBOL_TABLE[id][SYMBOL]);

	if (ft_strncmp(str, SYMBOL_TABLE[id][SYMBOL], symbol_len) == 0)
		return (symbol_len);
	return (-1);
}

t_toklen	count_consecutive_symbols(const char *str, t_symbol_id id)
{
	const char	*ws = (const char *)SYMBOL_TABLE[id][SYMBOL];
	t_toklen	len;
	
	len = 0;
	while(str[len] == ws[0])
		++len;
	if (len == 0)
		return (-1);
	return (len);

}

t_toklen	word_len(const char *str, t_symbol_id id)
{
	t_toklen	(*compare_symbol)(const char *, t_symbol_id id);
	t_toklen	len;
	bool	stopped;
	t_symbol_id	i;

	len = 0;
	stopped = false;
	while (!stopped)
	{
		++len;
		i = 0;
		while (i < id)
		{
			compare_symbol = SYMBOL_TABLE[i][FN_PTR];
			if (compare_symbol(str + len, i) != -1)
			{
				stopped = true;
				break ;
			}
			++i;
		}
	}
	return (len);
}

// tokenizes lexer input, and increments lexer ptr...
t_token	tokenize_one(t_lexer *lexer)
{
	const char	*token_start = lexer->begin + lexer->cur;
	t_toklen	(*matching_symbol_fn)(const char *, t_symbol_id);
	t_toklen	new_len;
	t_symbol_id	id;

	id = 0;
	while (id < SYMBOL_ID_COUNT)
	{
		matching_symbol_fn = SYMBOL_TABLE[id][FN_PTR];
		new_len = matching_symbol_fn(token_start, id);
		if (new_len > -1)
		{
			assert(token_start + new_len <= lexer->end && "Lexer incremented past end");
			lexer->cur += new_len;
			return (t_token)
			{
				.id = id,
				.begin = token_start,
				.end = token_start + new_len,
			};
		}
		++id;
	}
	return (t_token) { .id = UNHANDLED_SYMBOL, .begin = NULL, .end = NULL};
}

bool	is_one_of_ids(t_token *token, const uint64_t *ids, size_t count_ids)
{
	while (count_ids--)
	{
		if (*ids == token->id)
			return (true);
		++ids;
	}
	return (false);
}

bool	has_id(t_token *token, const uint64_t id)
{
	return(is_one_of_ids(token, &id, 1));
}

bool	get_next_token(t_lexer *lexer, t_token *token)
{
	const uint64_t	whitespace[3] = {SPACE, TAB, NEW_LINE};

	*token = tokenize_one(lexer);
	if (is_one_of_ids(token, whitespace, 3))
		return (get_next_token(lexer, token));
	return (!is_one_of_ids(token, (uint64_t[]){END, UNHANDLED_SYMBOL}, 2));

}


bool	get_next_token_incl_whitespace(t_lexer *lexer, t_token *token)
{
	*token = tokenize_one(lexer);
	return (!is_one_of_ids(token, (uint64_t[]){END, UNHANDLED_SYMBOL}, 2));
}

/*
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
		token.lst_data.prev = NULL;
		token.lst_data.next = NULL;
		*new_token = token;// BUG:Does this copy all of the data correctly? no memcpy required?
		ft_sll_addback(&head, (t_lst_embed *)new_token);
	}
	return ((t_token *)head);
}

// malloc's space for token lst struct and initializes it IF a valid ptr is psdlfkjdffassed in
struct s_token	*lst_new_token(struct s_token token)
{
	struct s_token	*token_mem;

	token_mem = (struct s_token *)malloc(sizeof(struct s_token));
	if (!token_mem)
		return (NULL);
	*token_mem = token;
	return (token_mem);
}

// NOTE: Is it needed to add identifier for double character token_count?
t_token	tokenize_one_token(struct s_tokenizer *tokenizer)
{
	char		*str;
	t_token		token;

	str = tokenizer->input;
	token.text = str;
	token.identifier = (enum e_token_identifier)*str;
	token.length = 0;
	while (str[token.length] != END && ft_strchr(WHITE_SPACE, str[token.length]))
		++token.length;
	if (token.length > 0 || *str == END)
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
*/
