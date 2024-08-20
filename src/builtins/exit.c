/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:25:40 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/20 20:29:07 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	g_last_exit_code = 0;

static bool	is_out_of_range(int sign, unsigned long long number, bool *error_flag)
{
	if ((number > LONG_MAX)
	|| (sign == -1 && number > -(unsigned long)LONG_MIN))
	*error_flag = true;
	return(error_flag);
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
		number = number * 10 + str[i] - '0';
		if (is_out_of_range(sign, number, error_flag))
			break ;
		i++;
	}
	return (number * sign);
}

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
	while (arg[i])
	{
		if ((!ft_isdigit(arg[i]) && (arg[i] >= '\t' && arg[i] <= '\r')) || arg[i] == ' ')
			*error_flag = true;
		i++;
	}
	i = ft_atoi_long(arg, error_flag);
	printf("i=%llu\n", i);
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
	printf("in exit_builtin\n");
	printf("in exit, args[1]=%s\n", args[1]);
	int		exit_code;
	bool	error_flag;
	bool	piped;

	piped = is_exit_piped(data);
	printf("piped=%d\n", piped);
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
				printf("exit_code=%d\n", exit_code);
	exit_shell(data, exit_code);
	return (2);
}