/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:27:37 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/10/05 20:18:48 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	**realloc_env_vars(t_data *data, int env_count)
{
	char	**env_realloc;
	int		i;

	env_realloc = ft_calloc(env_count + 1, sizeof(env_realloc));
	if (!env_realloc)
		return (NULL);
	i = 0;
	while (data->env[i] && i < env_count)
	{
		env_realloc[i] = ft_strdup(data->env[i]);
		free(data->env[i]);
		i++;
	}
	free(data->env);
	return (env_realloc);
}

bool	set_env(t_data *data, char *key, char *value)
{
	int		env_index;
	char	*tmp;

	env_index = get_env_index(data->env, key);
	if (!value)
			value = "";
		tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (env_index != -1)
	{
		free(data->env[env_index]);
		data->env[env_index] = ft_strjoin(key, tmp);
	}
	else
	{
		env_index = env_var_count(data->env);
		data->env = realloc_env_vars(data, env_index + 1);
		if (!data->env)
			return (false);
		data->env[env_index] = ft_strjoin(key, tmp);
	}
	free(tmp);
	return (true);
}

bool	unset_env(t_data *data, int env_index)
{
	if (env_index > env_var_count(data->env))
		return (false);
	free(data->env[env_index]);
	while (data->env[env_index + 1])
	{
		data->env[env_index] = ft_strdup(data->env[env_index + 1]);
		free(data->env[env_index + 1]);
		env_index++;
	}
	data->env = realloc_env_vars(data, env_index);
	if (!data->env)
		return (false);
	return (true);
}
