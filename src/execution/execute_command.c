/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:10:59 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/07/22 19:30:00 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	execute_builtin(t_data *data, t_command *cmd)
{
	if (ft_strncmp(cmd->name, "cd", 3) == 0)
		return(cd(data, cmd->args, cmd->argc));
	else if (ft_strncmp(cmd->name, "echo", 5) == 0)
		return(echo(cmd->args));
	else if (ft_strncmp(cmd->name, "env", 4) == 0)
		return(env(data, cmd->args));
	else if (ft_strncmp(cmd->name, "export", 7) == 0)
		return(export(data, cmd->args));
	else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		return(pwd(data));
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		return(unset(data, cmd->args));
	// else if (ft_strncmp(cmd->command, "exit", 5) == 0)
	// return(exit(data, cmd->args));
	return (CMD_NOT_FOUND);
}

//If the command is in the current directory, you need to use ./command to run it:
// ./mycommand
//if mycommand is not a built-in or external shell command but an executable file present 
//in a specific location on the filesystem:
// /usr/local/bin/mycommand if the command is in /usr/local/bin.
int	execute_command(t_data *data, t_command *cmd)
{
	int	status;
	status = 1;
	if (ft_strchr(cmd->name, '/') == NULL)
	{
		status = execute_builtin(data, cmd);
		// if (status != CMD_NOT_FOUND)//if it is a builtin command
		//exit(1);
	}
	return (status);
}