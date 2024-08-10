#include "../../incl/minishell.h"

static char **get_paths_from_env(t_data *data)
{
	char **env_paths_array;

	if (get_env_index(data->env, "PATH") == -1)//if the PATH exists in data->env
		return (NULL);
	env_paths_array = ft_split(get_env_value(data->env, "PATH"), ':');
	if (!env_paths_array)
		return (NULL);
	return (env_paths_array);
}

static char	*find_valid_command_path(char *command, char **env_paths_array)
{
	int		i;
	char	*command_path;

	command_path = NULL;
	i = 0;
	while (env_paths_array[i])// /usr/bin
	{
		command_path = ft_strjoin(env_paths_array[i], command);// /usr/bin/ls
		if (!command_path)
		{
			error_msg_command("malloc", NULL,
				"an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(command_path, F_OK | X_OK) == 0)
			return (command_path);
		free_ptr(command_path);
		i++;
	}
	return (NULL);
}

char	*get_command_path(t_data *data, char *command_name)
{
	char	**env_paths_array;
	char	*command;
	char	*command_path;

	if (!command_name)
		return (NULL);
	env_paths_array = get_paths_from_env(data);
	if (!env_paths_array)
		return (NULL);
	command = ft_strjoin("/", command_name);
	if (!command)
	{
		free_str_arr(env_paths_array);
		return (NULL);
	}
	command_path = find_valid_command_path(command, env_paths_array);
	if (!command_path)
	{
		free_ptr(command);
		free_str_arr(env_paths_array);
		return (NULL);
	}
	return (command_path);
}