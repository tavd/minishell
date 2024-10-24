#include "libft/libft.h"

//#include "libft/lst.h"

/*
*	An enum for more readable code. "ENV_VAR" is not an accurate name for '$',
*	but in the case of minishell it is exhaustive of the chars function. Right?
*/
// TODO: make it possible for heredoc to set a word as END delimiter...
// TODO: INVESTIGATE:
//	 x echo= ="hello = wi"
//	=hello = wi: command not found
enum e_identifiers
{
	END,
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

	// ... not sure about these yet
	HEREDOC_END,
};

// NOTE: Whitespace should only be reduced while or after all subtitutions?
#define WHITE_SPACE_CHARS SPACE, TAB, NEW_LINE

const static char	WHITE_SPACE[4] = {
	WHITE_SPACE_CHARS, '\0'
};

# define SINGLE_TOKEN_CHARS \
	SINGLE_QUOTE, DOUBLE_QUOTE, \
	OPEN_BRACE, CLOSE_BRACE, REDIRECT_IN, REDIRECT_OUT, \
	PIPE, ENV_VAR, SET_ENV_VAR, QUESTION_MARK

const static char	SINGLE_TOKENS[11] = {
	  SINGLE_TOKEN_CHARS, '\0'
};

// Maybe combining is too inflexible for some cases?
const static char	WORD_DELIMITERS[14] = {
	WHITE_SPACE_CHARS, SINGLE_TOKEN_CHARS, '\0'
};
	// SPACE, TAB, NEW_LINE,
	// SINGLE_QUOTE, DOUBLE_QUOTE, REDIRECT_IN, REDIRECT_OUT,
	// PIPE, SET_ENV, ENV_VAR, END


struct s_tokenizer {
	char	*input;
};

typedef struct s_token {
	char			*text;
	ssize_t			length; // size_t?
	enum e_identifiers	identifier;
}	t_token;

void	init_tokenizer(struct s_tokenizer *tokenizer, char *str_to_tokenize);

t_token	tokenize_one_token(struct s_tokenizer *tokenizer);
t_list	*tokenize_all_tokens(struct s_tokenizer *tokenizer);

