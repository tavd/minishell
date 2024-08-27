/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:19:22 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/27 20:27:54 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incl/libft.h"
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

# define SUCCESS 0
# define FAILURE 1

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define PROMPT2 "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"


typedef struct s_io
{
	char	*infile_name;
	char	*outfile_name;
	int		fd_infile;
	int		fd_outfile;
	int		stdin_copy;
	int		stdout_copy;
}	t_io;

typedef struct s_command
{
	char				*name;
	char				*path;
	char				**args;
	bool				is_piped;
	int					*pipe_fd;
	t_io				*io;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_token
{	

	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char		**env;
	char		*working_dir;
	char		*old_working_dir;
	t_command	*cmd;
	pid_t		pid;
	bool		interactive;
	// t_token		*token;
	char		*user_input;
}	t_data;

// bool	init_data(t_data *data, char **env);
// void	init_io(t_command *cmd);

#endif