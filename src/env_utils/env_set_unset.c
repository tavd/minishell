/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:27:37 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/10/02 17:51:14 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	**realloc_env_vars(t_data *data, int env_count)
{
	char	**env_realloc;
	int		i;

	env_realloc = ft_calloc(env_count + 1, sizeof(env_realloc));//+1 for NULL
	if (!env_realloc)
		return (NULL);
	i = 0;
	while (data->env[i] && i < env_count)
	{
		env_realloc[i] = ft_strdup(data->env[i]);//env_realloc[i] = data->env[i];
		free_ptr(data->env[i]);
		i++;
	}
	free(data->env);
	return (env_realloc);
}

bool	set_env(t_data *data, char *key, char *value)
{
	int		env_var_index;
	char	*tmp;

	env_var_index = get_env_index(data->env, key);
	if (!value)//if we want to add a key without a value like "key="
			value = "";
		tmp = ft_strjoin("=", value);
	if (!tmp)//if malloc in ft_strjoin fails
		return (false);
	if (env_var_index != -1)//if the key exists
	{
		free_ptr(data->env[env_var_index]);//remove the old entry
		data->env[env_var_index] = ft_strjoin(key, tmp);//rewrite the value
	}
	else
	{
		env_var_index = env_var_count(data->env);
		data->env = realloc_env_vars(data, env_var_index + 1);//add new env var, +1 for the new entry
		if (!data->env)
			return (false);
		data->env[env_var_index] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}

bool	unset_env(t_data *data, int env_var_index)
{
	int	i;

	if (env_var_index > env_var_count(data->env))//invalid index
		return (false);
	free_ptr(data->env[env_var_index]);
	i = env_var_index;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		i++;
	}
	data->env = realloc_env_vars(data, i);
	if (!data->env)
		return (false);
	return (true);
}
