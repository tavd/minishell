/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:52:06 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/16 21:24:26 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	env(t_data *data, char **args)
{
	int	i;

	if (args && args[1])//if there are args after the env
		return (error_msg_command("env", NULL, "too many arguments", 2));//return 2
	if (!data->env)
		return (EXIT_FAILURE);
	i = 0;
	while (data->env[i])
		ft_putendl_fd(data->env[i++], STDOUT_FILENO);//print each env substring followed by a \n
	return (EXIT_SUCCESS);
}
