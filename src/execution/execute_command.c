/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:10:59 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/05 19:43:23 by tavdiiev         ###   ########.fr       */
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

static int execute_external_command(t_data *data, t_command *cmd)
{
	if (!cmd->name || cmd->name[0] == '\0')
		return (CMD_NOT_FOUND);
	if (command_is_dir(cmd->name))
		return (CMD_NOT_FOUND);
	cmd->path = get_command_path(data, cmd->name);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		error_msg_command("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

//If the command is in the current directory, you need to use ./command to run it:
// ./mycommand
//if mycommand is not a built-in or external shell command but an executable file present 
//in a specific location on the filesystem:
// /usr/local/bin/mycommand if the command is in /usr/local/bin.
static int	execute_local_binary_or_absolute_path(t_data *data, t_command *command)
{
	int status;

	status = is_command_not_found(data, command);
	if (status)
		return (status);
	if (execve(command->name, command->args, data->env) == -1)
		return (error_msg_command("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

int	execute_command(t_data *data, t_command *command)
{
	int	status;
	
	if (!command || !command->name)
		exit_shell(data, errmsg_cmd("child", NULL,
				"parsing error: no command to execute!", EXIT_FAILURE));
	if (!is_valid_fd(command->io))
		exit_shell(data, EXIT_FAILURE);
	redirect_pipe_fds(data->cmd, command);
	redirect_stdin_stdout(command->io);
	close_fds(data->cmd, false);
	if (!ft_strchr(command->name, '/'))
	{
		status = execute_builtin(data, command);
		if (status != CMD_NOT_FOUND)//if it is a builtin command
		exit_shell(data, status);
		status = execute_external_command(data, command);
		if (status != CMD_NOT_FOUND)
		exit_shell(data, status);
	}
	status = execute_local_binary_or_absolute_path(data, command);
	exit_shell(data, status);
	return (status);
}