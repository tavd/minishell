#include "../../incl/minishell.h"

static bool	init_env(t_data *data, char **env)
{
	int		i;

	data->env = ft_calloc(env_var_count(env) + 1, sizeof(data->env));
	if (!data->env)
		return (false);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (false);
		i++;
	}
	return (true);
}

static bool	init_working_directories(t_data *data)
{
	char	buf[PATH_MAX];
	char	*working_dir;

	working_dir = getcwd(buf, sizeof(buf));
	data->working_dir = ft_strdup(working_dir);
	if (!data->working_dir)
		return (false);
	if (get_env_index(data->env, "OLDPWD") != -1)
	{
		data->old_working_dir = ft_strdup(get_env_value(data->env,
					"OLDPWD"));
		if (!data->old_working_dir)
			return (false);
	}
	else
	{
		data->old_working_dir = ft_strdup(working_dir);
		if (!data->old_working_dir)
			return (false);
	}
	return (true);
}

bool	init_data(t_data *data, char **env)
{
	if (!init_env(data, env))
	{
		error_msg_command("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
	if (!init_working_directories(data))
	{
		error_msg_command("Fatal", NULL, "Could not initialize working directories",
			1);
		return (false);
	}
	data->cmd = NULL;
	data->pid = -1;
	g_last_exit_code = 0;
	return (true);
}

void	init_io(t_command *cmd)
{
	if (!cmd->io)
	{
		cmd->io = malloc(sizeof(t_io));
		if (!cmd->io)
			return ;
		cmd->io->infile_name = NULL;
		cmd->io->outfile_name = NULL;
		cmd->io->fd_infile = -1;
		cmd->io->fd_outfile = -1;
		cmd->io->stdin_copy = -1;
		cmd->io->stdout_copy = -1;
	}
	printf("init_io: cmd->io=%p\n", cmd->io);
	printf("the end of init_io\n");
}