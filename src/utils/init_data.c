#include "../../incl/minishell.h"

bool	init_data(t_data *data, char **env)
{
	if (!init_env(data, env))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
	if (!init_wds(data))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize working directories",
			1);
		return (false);
	}
	// data->token = NULL;
	// data->user_input = NULL;
	data->cmd = NULL;
	data->pid = -1;
	// g_last_exit_code = 0;
	return (true);
}

void	init_io(t_command *cmd)
{
	if (!cmd->io)
	{
		cmd->io = malloc(sizeof * cmd->io);
		if (!cmd->io)
			return ;
		cmd->io->infile_name = NULL;
		cmd->io->outfile_name = NULL;
		char	*heredoc_delimiter = NULL;
		bool	heredoc_quotes = false;
		cmd->io->fd_in = -1;
		cmd->io->fd_out = -1;
		cmd->io->stdin_copy = -1;
		cmd->io->stdout_copy = -1;
	}
}