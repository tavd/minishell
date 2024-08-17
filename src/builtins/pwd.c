/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:31:41 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/17 20:43:30 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int pwd(t_data *data)
{
	if (data->working_dir)
	{
		printf("in if data->working_dir\n");
		ft_putendl_fd(data->working_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	error_msg_command("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
