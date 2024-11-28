/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:25:44 by mzwart            #+#    #+#             */
/*   Updated: 2024/11/22 10:25:44 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
# include "lst_embed.h"

#ifndef TOKENIZER_H_
# define TOKENIZER_H_

typedef struct s_tokenizer {
	char	*begin;
	char	*end;
	size_t	cur;
}	t_tokenizer;
	//int	line_number;
typedef struct s_tokenizer t_lexer;

typedef struct s_token {
	uint64_t		id;
	char			*begin;
	char			*end;
}	t_token;

/*
 * NOTE: "struct s_lst_embed" has to be the first member of the struct
 * to allow for casting between t_lst_embed to t_lst_token, without offsets
 */
typedef struct s_lst_token {
	struct s_lst_embed	lst_data;
	uint64_t		id;
	char			*begin;
	char			*end;
}	t_lst_token;
/*
 * NOTE: Ideally to access a struct within a struct you would abstract this
 * away using a macro function(linux kernel: container_of), as this would
 * remove the need for the lst_embed being the first member of the struct
 */

// this kind of mental overhead + its dependent one the struct's memory layout.
// But since we can't use macro functions (Norm) its the second best thing

typedef enum e_tokenizer_symbol_id
{
	END,
	SPACE,
	TAB,
	NEW_LINE,
	PIPE,
	DOLLAR_SIGN,
	EQUAL_SIGN,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	HEREDOC,
	APPEND_MODE,
	REDIRECT_IN,
	REDIRECT_OUT,
	WORD,
	SYMBOL_ID_COUNT,
}	t_symbol_id;

#define UNHANDELED_SYMBOL -1

bool	is_nullterm(const char *str, t_symbol_id id, size_t *newlen);
bool	symbol(const char *str, t_symbol_id id, size_t *newlen);
bool	whitespace(const char *str, t_symbol_id id, size_t *newlen);
bool	word(const char *str, t_symbol_id id, size_t *newlen);
bool	fallback(const char *str, t_symbol_id id, size_t *newlen);

// NOTE: longer strings should come before shorter strings
// if they share the same characters. (for example "<<" and "<")
_Static_assert(SYMBOL_ID_COUNT == 14, "symbol count has changed");
static const void	*SYMBOL_TABLE[SYMBOL_ID_COUNT][2] =
{
	[END] =			{"\0", symbol},
	[SPACE] =		{" ", whitespace},
	[TAB] =			{"\t", whitespace},
	[NEW_LINE] =		{"\n", symbol},
	[PIPE] =		{"|", symbol},
	[DOLLAR_SIGN] =		{"$", symbol},
	[EQUAL_SIGN] =		{"=", symbol},
	[SINGLE_QUOTE] =	{"\'", symbol},
	[DOUBLE_QUOTE] =	{"\"", symbol},
	[HEREDOC] =		{"<<", symbol},
	[APPEND_MODE]		{">>", symbol},
	[REDIRECT_IN] =		{"<", symbol},
	[REDIRECT_OUT] =	{">", symbol},
	[WORD] =		{"WORD", word},
	[DEFAULT_FALLBACK] =	{"other", fallback},
};

#define SYMBOL 0
#define FN_PTR 1

t_lexer	create_tokenizer(const char *input_begin, const char *input_end);
// t_token	tokenize_one_token(struct s_tokenizer *tokenizer);
// t_token	*tokenize_all_tokens(struct s_tokenizer *tokenizer);


#define UNHANDELED_SYMBOLS false
#define SUCCESS true

bool	get_next_token(t_lexer *lexer, t_token *token);
bool	get_next_token_incl_whitespace(t_lexer *lexer, t_token *token);


#endif
/*================================================================================*/

/*
// These are both the identifiers that the tokenizer and parser creates...
typedef enum e_token_identifier
{
	END = '\0',
	WORD,
	SPACE = ' ',
	NEW_LINE = '\n',
	TAB = '\t',
	ENV_VAR = '$',
	SET_ENV_VAR = '=',
	QUESTION_MARK = '?',
	PIPE = '|',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	APPEND_MODE,
	HEREDOC_MODE,
	SET_EXIT_STATUS,
	HEREDOC_UNQUOTED_WORD,
} t_tok_id_old;

// // NOTE: longer strings should come before shorter strings
// // if they share the same characters. (for example "<<" and "<")
// static_assert(SYMBOL_COUNT == 14, "symbol count has changed");
// static const char	*SYMBOLS[SYMBOL_COUNT]
// {
// 	[END] = "\0",
// 	[SPACE] = " ",
// 	[TAB] = "\t",
// 	[NEW_LINE] = "\n",
// 	[PIPE] = "|",
// 	[DOLLAR_SIGN] = "$",
// 	[EQUAL_SIGN] = "=",
// 	[SINGLE_QUOTE] = "\'",
// 	[DOUBLE_QUOTE] = "\"",
// 	[HEREDOC] = "<<",
// 	[APPEND_MODE] ">>",
// 	[REDIRECT_IN] = "<",
// 	[REDIRECT_OUT] = ">",
// 	[WORD],
// }

// NOTE: Whitespace should only be reduced while or after all subtitutions?
#define WHITE_SPACE_CHARS SPACE, TAB, NEW_LINE

static const char	WHITE_SPACE[4] = {
	WHITE_SPACE_CHARS
};

# define SINGLE_TOKEN_CHARS \
	SINGLE_QUOTE, DOUBLE_QUOTE, \
	OPEN_BRACE, CLOSE_BRACE, REDIRECT_IN, REDIRECT_OUT, \
	PIPE, ENV_VAR, SET_ENV_VAR, QUESTION_MARK

static const char	SINGLE_TOKENS[11] = {
	  SINGLE_TOKEN_CHARS, '\0'
};

// Maybe combining is too inflexible for some cases?
static const char	WORD_DELIMITERS[14] = {
	WHITE_SPACE_CHARS, SINGLE_TOKEN_CHARS, '\0'
};
	// SPACE, TAB, NEW_LINE,
	// SINGLE_QUOTE, DOUBLE_QUOTE, REDIRECT_IN, REDIRECT_OUT,
	// PIPE, SET_ENV, ENV_VAR, END

// TODO: INVESTIGATE bash shell cmd:
//	 x echo= ="hello = wi"
//	=hello = wi: command not found
*/
