/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:26:32 by irsander          #+#    #+#             */
/*   Updated: 2024/08/10 18:24:52 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incl/libft.h"
# include "prompt.h"
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

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

# define SUCCESS 0
# define FAILURE 1

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

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
	int					argc;
	bool				is_piped;
	int					*pipe_fd;
	t_io				*io;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;


typedef struct s_data
{
	char		**env;
	char		*working_dir;
	char		*old_working_dir;
	t_command	*cmd;
	pid_t		pid;
}	t_data;

bool	init_data(t_data *data, char **env);
void	init_io(t_command *cmd);
// builtins
int			echo(char **args);
int			env(t_data *data, char **args);
int			pwd(t_data *data);
int			export(t_data *data, char **args);
int			unset(t_data *data, char **args);
int			cd(t_data *data, char ** args, int argc);

bool		is_valid_key(char *key);
int			get_env_index(char **env, char *key);
int			env_var_count(char **env);
char		*get_env_value(char **env, char *key);
// env_utils/env_set_unset.c
bool	set_env(t_data *data, char *key, char *value);
bool	unset_env(t_data *data, int env_var_index);
//env_utils
int	get_env_index(char **env, char *key);
int	env_var_count(char **env);
char	*get_env_value(char **env, char *key);

// execute.c
int			execute(t_data *data);
int			execute_command(t_data *data, t_command *cmd);
int			execute_builtin(t_data *data, t_command *cmd);
// error.c
int	error_msg_command(char *command, char *detail, char *error_message, int error_number);
//free.c
void	free_str_arr(char **tab);
void	free_ptr(void *ptr);
void	close_fds(t_command *cmd_list, bool close_copies);
//utils.c
bool	command_is_dir(char *cmd);
int		is_command_not_found(t_data *data, t_command *command);
//execution/get_path.c
char	*get_command_path(t_data *data, char *command_name);
//io.c
bool	is_valid_fd(t_io *io);
bool	redirect_io_file(t_io *io);
bool	restore_stdin_stdout(t_io *io);
//pipe.c
bool	create_pipes(t_data *data);
void	close_pipe_fds(t_command *cmds, t_command *own_cmd);
bool	redirect_io_pipe(t_command *cmds, t_command *this_cmd);
//exit_shell.c
void	exit_shell(t_data *data, int exit_number);
#endif