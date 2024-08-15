/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:53:39 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/14 17:30:49 by tavdiiev         ###   ########.fr       */
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

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static void	print_args(char **args, bool is_n, int i)
{
	if (!args[i] && !is_n)//only echo (without args or -n)
	{
		// printf("echo print\n");
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

int	echo(char **args)
{
	int		i;
	bool	is_n_fl;

	is_n_fl = false;
	i = 1;
	// printf("args[1]=%s\n",args[1]);
	//printf("in echo\n");
	while (args[i] && is_n(args[i]))//if there is 1 or more -n args in a row, starting from the 1st arg
	{                               //(echo -n dfg fg, echo -n -n -n -n dfg dg)
		is_n_fl = true;
		i++;
		//printf("in echo while\n");
	}
	//printf("in echo after while\n");
	print_args(args, is_n_fl, i);
	return (EXIT_SUCCESS);
}
