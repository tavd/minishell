/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:31:41 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/10/11 20:48:19 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int pwd(void)
{
	char	buf[PATH_MAX];
	char	*current_working_dir;

	current_working_dir = getcwd(buf, PATH_MAX);
	if (!current_working_dir)
		error_msg_command("pwd", NULL, strerror(errno), errno);
	else
	{
		ft_putendl_fd(current_working_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);		
	}
	return (EXIT_FAILURE);
}
