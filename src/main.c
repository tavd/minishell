/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:30:21 by irsander          #+#    #+#             */
/*   Updated: 2024/07/22 19:31:26 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_env(t_data *data, char **env)
{
	int		i;

	data->env = ft_calloc(env_var_count(env) + 1, sizeof * data->env);
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
	data->cmd = NULL;
	return (true);
}

static bool	init_wds(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->working_dir = ft_strdup(wd);
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
		data->old_working_dir = ft_strdup(wd);
		if (!data->old_working_dir)
			return (false);
	}
	return (true);
}

int main(int argc, char **argv, char **envp)
{
    (void)argv;
    t_data data;

	init_env(&data, envp);
	init_wds(&data);
	t_command command;
	command.args = argv;
	command.argc = argc;
	command.name = "cd";
	printf("res=%d\n",execute_command(&data, &command));
	pwd(&data);
	// int i = 0;
	// 	while (data.env[i])
	// ft_putendl_fd(data.env[i++], STDOUT_FILENO);
    return (0);
}