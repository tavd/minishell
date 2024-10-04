/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:14:59 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/10/01 20:12:11 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	is_valid_key(char *key)
{
	int i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (false);
	i++;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static char	**get_key_value_pair(char *arg)
{
	char	**key_val_array;
	char	*pos;

	pos = ft_strchr(arg, '=');
	key_val_array = malloc(sizeof(char *) * 3);
	key_val_array[0] = ft_substr(arg, 0, pos - arg);
	key_val_array[1] = ft_substr(pos, 1, ft_strlen(pos));
	key_val_array[2] = NULL;
	return (key_val_array);
}

//export   (no args) - undefined behavior
//export key=value
//export VAR1=value1 VAR2=value2 VAR3=value3
int	export(t_data *data, char **args)
{
	int		i;
	char	**tmp;

	i = 1;
	if (!args[i])//export without args
	 return (env(data, NULL));
	while (args[i])
	{
		if(!is_valid_key(args[i]))
		{
		error_msg_command("export", args[i], "not a valid identifier:", 0);
		return(EXIT_FAILURE);			
		}
		else if (ft_strchr(args[i], '='))//if there is '=' 
		{
		tmp = get_key_value_pair(args[i]);
		set_env(data, tmp[0], tmp[1]);
		free_str_arr(tmp);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
