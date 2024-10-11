#include "../../incl/minishell.h"

static char **get_path_dirs(t_data *data)
{
	char **paths_array;

	if (get_env_index(data->env, "PATH") == -1)//if the PATH exists in data->env
		return (NULL);
	paths_array = ft_split(get_env_value(data->env, "PATH"), ':');
	if (!paths_array)
		return (NULL);
	return (paths_array);
}

static char	*find_valid_command_path(char *command, char **paths_array)
{
	int		i;
	char	*command_path;

	command_path = NULL;
	i = 0;
	while (paths_array[i])// /usr/bin...
	{
		command_path = ft_strjoin(paths_array[i], command);// /usr/bin/ls
		if (!command_path)
		{
			error_msg_command("malloc", NULL, "an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(command_path, F_OK | X_OK) == 0)
			return (command_path);
		free(command_path);
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
	env_paths_array = get_path_dirs(data);
	if (!env_paths_array)
		return (NULL);
	command = ft_strjoin("/", command_name);
	if (!command)
	{
		free_char_arr(env_paths_array);
		return (NULL);
	}
	command_path = find_valid_command_path(command, env_paths_array);
	if (!command_path)
	{
		free(command);
		free_char_arr(env_paths_array);
		return (NULL);
	}
	return (command_path);
}
