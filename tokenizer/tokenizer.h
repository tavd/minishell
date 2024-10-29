#include "libft/libft.h"

// #include "libft/embedded_lst.h"
// #include "libft/generic_lst.h"

//#include "libft/lst.h"

/*
*	An enum of all possible tokens. "ENV_VAR" is not an accurate name for '$',
*	but in the case of minishell it is exhaustive of the chars function. Right?
*/

// TODO: make it possible for heredoc to set a word as END or use HEREDOC_END as delimiter...
// TODO: INVESTIGATE:
//	 x echo= ="hello = wi"
//	=hello = wi: command not found

// These are both the identifiers that the tokenizer and parser creates...
enum e_token_identifier
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
	OPEN_BRACE = '{',
	CLOSE_BRACE = '}',
	PARSER_EXIT_STATUS,
	PARSER_HEREDOC_END,
};

// NOTE: Whitespace should only be reduced while or after all subtitutions?
#define WHITE_SPACE_CHARS SPACE, TAB, NEW_LINE

static const char	WHITE_SPACE[4] = {
	WHITE_SPACE_CHARS, '\0'
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


struct s_tokenizer {
	char	*input;
};

// TODO: add to libft with new functions...
typedef struct s_lst_embed
{
	struct s_lst_embed	*prev;
	struct s_lst_embed	*next;
}	t_lst_embed;

// NOTE: the member: "struct s_lst_embed" has to importantly be the first
// as this allows for easy casting from lst_embed to t_token.
typedef struct s_token {
	struct s_lst_embed	lst_info;
	enum e_token_identifier	identifier;
	char			*text;
	ssize_t			length; // size_t?
}	t_token;
// NOTE: Ideally you wouldn't need to worry about casting to t_token from
// t_lste_embed to acces the members you want, since good code abstract's away
// this kind of mental overhead + its dependent one the struct's memory layout.
// But since we can't use macro functions (Norm) its the second best thing

void	init_tokenizer(struct s_tokenizer *tokenizer, char *str_to_tokenize);

t_token	tokenize_one_token(struct s_tokenizer *tokenizer);
t_token	*tokenize_all_tokens(struct s_tokenizer *tokenizer);

