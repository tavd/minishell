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

int	matching_token_id(const uint64_t *target_ids, size_t count_ids, t_token *tok)
{
	size_t	i;

	i = 0;
	while (i < count_ids)
	{
		if (target_ids[i] == tok->id)
			return (target_ids[i]);
		++i;
	}
	return (0);
}

size_t	_symbol(const char *str, const char *symbol_from_table)
{
	const size_t	symbol_len = ft_strlen(symbol_from_table);

	if (ft_strncmp(str, symbol_from_table, symbol_len) == 0)
		return (symbol_len);
	return (0);
}

size_t	_whitespace(const char *str, const char *symbol_from_table)
{
	size_t	len;

	len = 0;
	while(str[len] == *symbol_from_table)
		++len;
	return (len);
}

size_t	_word(const char *str, const char*)
{
	size_t	len;
	int	i;
	
	len = 0;
	while (true)
	{
		i = 0;
		while (i < WORD)
		{
			if (str[len] == *((char *)SYMBOL_TABLE[i][0]))
				return (len);
			++i;
		}
		++len;
	}
	return (0);
}

// tokenizes lexer input, and increments lexer ptr...
t_token	tokenize_one(t_lexer *lexer)
{
	const char	*lexer_start = lexer->begin + lexer->cur;
	size_t		(*matching_symbol_fn)(const char *, const char *);
	size_t		symbol_len;
	int		id;

	id = 0;
	while (id < SYMBOL_ID_COUNT)
	{
		matching_symbol_fn = SYMBOL_TABLE[id][FN_PTR];
		symbol_len = matching_symbol_fn(lexer_start, SYMBOL_TABLE[id][SYMBOL]);
		if (symbol_len > 0)
		{
			lexer->cur += symbol_len;
			return (t_token)
			{
			.id = id,
			.begin = lexer_start,
			.end = lexer_start + symbol_len,
			}
		}
		++id;
	}
	return (t_token) { .id = UNHANDELD_SYMBOL, .begin = NULL, .end = NULL};
}

	if (id == LEXER_END || id == SYMBOL_ID_COUNT)
		return (false);
	assert(("Lexer is incremented past the lexer.end", lexer->begin + lexer->cur + (token->end - token->begin) <= lexer->end));
	lexer->cur += (token->end - token->begin); // The length of END is 0 so no increment needed...
	return (true);
}

bool	get_next_token_incl_whitespace(t_lexer *lexer, t_token *token)
{
	token = tokenize_one(lexer);
	if (token == (t_token){0} || token->id == END)
		return (false);
	assert(("Lexer is incremented past the lexer.end", lexer->begin + lexer->cur + (token->end - token->begin) <= lexer->end));
	lexer->cur += (token->end - token->begin); // The length of END is 0 so no increment needed...
	return (true);

}

bool	get_next_token(t_lexer *lexer, t_token *token)
{
	const uint64_t	WHITESPACE[3] = {SPACE, TAB, NEW_LINE};

	token = tokenize_one(lexer);
	if (token == (t_token){0} || token->id == END)
		return (false);
	if (matching_token_id(WHITESPACE, 3, token))
		return (get_next_token(lexer, token));
	return (true);

}


token	tokenize_one(t_lexer *lexer)
{

}


bool	get_next_token(t_lexer *lexer, t_token *token)
{
	const uint64_t	WHITESPACE[3] = {SPACE, TAB, NEW_LINE};
	bool	fn_state;

	fn_state = get_next_token_incl_whitespace(lexer, token);
	if (matching_token_id(WHITESPACE, 3, token))
		return (get_next_token_incl_whitespace(lexer, token));
	return (fn_state);
}


bool	get_next_token_incl_whitespace(t_lexer *lexer, t_token *token)
{
	size_t		(*matching_symbol_len)(const char *, const char *);
	int		id;

	token->begin = lexer->begin + lexer->cur;
	token->end = token->begin;
	id = 0;
	while (id < SYMBOL_ID_COUNT)
	{
		matching_symbol_len_fn = SYMBOL_TABLE[id][1];
		token->end += matching_symbol_len(token->begin, SYMBOL_TABLE[id][0]);
		if (token->end > token->begin)
		{
			token->id = id;
			break ;
		}
		++id;
	}
	if (id == END || id == SYMBOL_ID_COUNT) // IMPROVE RIGHT NOW!!!
		return (false);
	lexer->cur += (token->end - token->begin);
	assert(lexer->begin + lexer->cur <= lexer->end && "Lexer overstept end");
	return (true);
}

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_lexer l;
	t_token	t;
	
	if (argc != 2)
		return 0;
	char	*str = argv[1];
	l = create_tokenizer(str, str + ft_strlen(str));
	while (get_next_token(&l, &t))
	{
		printf("(%s:%.*s) at [%i]\n", (char *)SYMBOL_TABLE[t.id][0], (int)(t.end - t.begin), t.begin, l.cur);
		t = (t_token){0};
	}
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
