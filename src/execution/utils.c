/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:00:56 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/10/13 19:56:43 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//Checks if the command is a directory rather than an executable.
bool	command_is_dir(char *command_name)
{
	struct stat	file_info;

	ft_memset(&file_info, 0, sizeof(file_info));
	stat(command_name, &file_info);
	return (S_ISDIR(file_info.st_mode));
}

int	is_command_not_found(t_data *data, t_command *command)
{
	if (!ft_strchr(command->name, '/') && get_env_index(data->env, "PATH") != -1)
		return (error_msg_command(command->name, NULL, "command not found", 
				CMD_NOT_FOUND));
	if (command_is_dir(command->name))
		return (error_msg_command(command->name, NULL, "Is a directory", CMD_NOT_EXECUTABLE));
	if (access(command->name, F_OK) != 0)
		return (error_msg_command(command->name, NULL, strerror(errno), CMD_NOT_FOUND));
	if (access(command->name, X_OK) != 0)
		return (error_msg_command(command->name, NULL, strerror(errno),	CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
