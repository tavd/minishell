/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:31:41 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/14 19:21:37 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//The PATH_MAX constant is commonly used, which defines the maximum length of a path in the system.
int pwd(t_data *data)
{
	char buf[PATH_MAX];
	char *cwd;

	if (data->working_dir)
	{
		printf("in if data->working_dir\n");
		ft_putendl_fd(data->working_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(buf, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	error_msg_command("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
