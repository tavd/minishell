#include "../../incl/minishell.h"

//move to env_utils
//Searches for the given variable in the environment variables.
int	get_env_index(char **env, char *key)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)//search for strings containing "Key="
		{
		free_ptr(tmp);
		return (i);			
		}
		i++;
	}
	free_ptr(tmp);
	return (-1);
}

int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

char	*get_env_value(char **env, char *key)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_ptr(tmp);
	return (NULL);
}