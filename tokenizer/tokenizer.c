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
	bool	found_matching_id;

	found_matching_id = false;
	while (count_ids--)
		found_matching_id |= (*ids++ == token->id);
	return (found_matching_id);
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
