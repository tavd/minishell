/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:25:40 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/23 18:27:12 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static bool	is_out_of_range(int sign, unsigned long long number, bool *error_flag)
{
	if ((sign == 1 && number > LONG_MAX)
	|| (sign == -1 && number > -(unsigned long)LONG_MIN))
	*error_flag = true;		
	return(*error_flag);
}

static int	ft_atoi_long(const char *str, bool *error_flag)
{
	unsigned long long	number;
	int					sign;
	int					i;

	number = 0;
	sign = 1;
	i = 0;
	while((str[i] && (str[i] >= '\t' && str[i] <= '\r')) || str[i] == ' ')
			i++;		
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		number = number * 10 + (str[i] - '0');
		if (is_out_of_range(sign, number, error_flag))
			break ;			
		i++;
	}
	return (number * sign);
}
    // Exit codes in Unix-like systems (including Bash) are limited to the range of 0-255 because they are stored in an 8-bit value.
    // When you specify an exit code larger than 255, the value wraps around. This is effectively taking 
	// the modulo 256 of the specified exit code.
static int get_exit_code(char *arg, bool *error_flag)
{
	unsigned long long	i;

	if (!arg)
		return (g_last_exit_code);
	i = 0;
	while ((arg[i] >= '\t' && arg[i] <= '\r') || arg[i] == ' ')
			i++;		
	if (arg[i] == '\0')
		*error_flag = true;		
	if (arg[i] == '-' || arg[i] == '+')
			i++;		
		if (!ft_isdigit(arg[i]))
			*error_flag = true;
	while (arg[i])
	{
		if ((!ft_isdigit(arg[i]) && !((arg[i] >= '\t' && arg[i] <= '\r') || arg[i] == ' ')))
			*error_flag = true;			
		i++;
	}
	i = ft_atoi_long(arg, error_flag);
	return (i % 256);
}

//If piped, exits the child process with the provided 
//exit code and does not exit minishell. Doesn't print "exit"
static bool	is_exit_piped(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (true);
	return (false);
}

int	ft_exit(t_data *data, char **args)
{
	int		exit_code;
	bool	error_flag;
	bool	piped;

	piped = is_exit_piped(data);
	error_flag = false;
	if (!piped && data->interactive)
		ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		exit_code = g_last_exit_code;
	else
	{
		exit_code = get_exit_code(args[1], &error_flag);
		if (error_flag)
			exit_code = error_msg_command("exit", args[1],
					"numeric argument required", 2);
		else if (args[2])
			return (error_msg_command("exit", NULL, "too many arguments", 1));
	}
	exit_shell(data, exit_code);
	return (2);
}
