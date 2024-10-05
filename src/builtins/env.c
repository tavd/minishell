/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:52:06 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/10/05 19:30:37 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	env(t_data *data, char **args)
{
	int	i;

	if (args && args[1])
		return (error_msg_command("env", NULL, "too many arguments", 2));
	if (!data->env)
		return (EXIT_FAILURE);
	i = 0;
	while (data->env[i])
		ft_putendl_fd(data->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
