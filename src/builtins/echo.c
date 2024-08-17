/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:53:39 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/16 18:47:28 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static bool is_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (false);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (true);
	return (false);
}

static void	print_args(char **args, bool is_n, int i)
{
	if (!args[i] && !is_n)//only echo (without args or -n)
	{
	ft_putchar_fd('\n', STDOUT_FILENO);//print '\n' to stdout
	return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])// if there are multiple args separate them by ' '
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !is_n)//if there is no more args or -n print '\n' after the args
				ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	echo(char **args)//cmd->args
{
	int		i;
	bool	is_n_fl;

	is_n_fl = false;
	i = 1;//cmd1->args[0]=echo
	while (args[i] && is_n(args[i]))//if there is 1 or more -n args in a row, starting from the 1st arg
	{                               //(echo -n dfg fg, echo -n -n -n -n dfg dg)
		is_n_fl = true;
		i++;
	}
	print_args(args, is_n_fl, i);
	return (EXIT_SUCCESS);
}

int	echo_simple(char **args)
{
	int		i;

	i = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
		i++;
	else if (!args[i])
		ft_putchar_fd('\n', STDOUT_FILENO);
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])// if there are multiple args separate them by ' '
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !is_n(args[1]))
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
