/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:45:42 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/10/05 19:24:53 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	unset(t_data *data, char **args)
{
	int	i;
	int	env_index;

	i = 1;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
			return (EXIT_FAILURE);
		else
		{
			env_index = get_env_index(data->env, args[i]);
			if (env_index != -1)
				unset_env(data, env_index);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
