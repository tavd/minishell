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

t_tokenizer	create_tokenizer(const char *input_string)
{
	return (t_tokenizer) {
		.begin = input_string;
		.cur = 0;
		.line_number = 0;
	};
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

bool	is_default_word(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

bool	is_token_id(int target_id, t_token *tok);
uint64_t	has_one_of_token_id(uint64_t *target_ids, size_t count_ids, t_token *tok);

bool	tokenize_one_token(char *str)
{
	char	*(*tokenize_fn)(const char *, const char *);
	int	tok_id;
	t_token	tok;

	tok_id = 0;
	tok.begin = t->begin;
	while (tok_id < SYMBOL_COUNT)
	{
		tokenize_fn = SYMBOL_TABLE[tok_id][1];
		tok.end = tokenize_fn(tok.begin, SYMBOL_TABLE[tok_id][0]);
		if (tok.end > tok.begin)
			break ;
		else
			++tok_id;
	}
	if (expect_token_id(WHITESPACE, 3, tok.id) != -1)
}

bool	get_next_token(t_tokenizer *t, t_token *token)
{
	char	*(*tokenize)(const char *, const char *);
	int	id;

	token->begin = t->begin;
	id = 0;
	while (id < SYMBOL_COUNT)
	{
		token = tokenize(token->begin, SYMBOL_TABLE[id], ft_strlen(SYMBOL_TABLE[id]) == 0)



		
		else
			++tok_id;
	}
	if (id == SYMBOL_COUNT)
		return (0);
	return (1);
}

int	main()
{


	while (get_next_token(&t, &token))
	{
		token


	}

}

bool	get_next_token_incl_whitespace(t_tokenizer *t, t_token *tok)
{

}

t_token	tokenize_one(struct s_tokenizer *t)
{
	t_token	token;
	uin64_t	tok_id;

	token.begin = t->input[t->cur];
	token.end = t->input[t->cur];
	tok_id = 0;
	while (tok_id < SYMBOL_COUNT)
	{
		if (ft_strncmp(token.begin, SYMBOLS[tok_id]) == 0)
		{
			token.id = tok_id;
			break ;
		}
		
		++tok_id;
	}
	if (tok_id == SYMBOL_COUNT)
	{

	}
}

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
