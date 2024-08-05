/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:55:18 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/05 20:20:39 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	check_data_create_pipes(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->name)//no commands only infile or outfile
	{
		if (data->cmd->io
			&& !is_valid_fd(data->cmd->io))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))//create pipes if needed
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

static int	wait_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

static int	create_children(t_data *data)
{
	t_command	*current_command;

	current_command = data->cmd;
	while (data->pid != 0 && current_command)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (error_msg_command("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0)
			execute_command(data, current_command);//not builtins
		current_command = current_command->next;
	}
	return (wait_children(data));
}

int	execute(t_data *data)
{
	int	status;

	status = check_data_create_pipes(data);
	if (status != CMD_NOT_FOUND)
		return (status);
	if (!data->cmd->is_piped && !data->cmd->prev
	&& is_valid_fd(data->cmd->io))//no pipes, no prev command
	{
		redirect_stdin_stdout(data->cmd->io);
		status = execute_builtin(data, data->cmd);
		restore_stdin_stdout(data->cmd->io);
	}
	if (status != CMD_NOT_FOUND)//builtin
		return (status);
	return (create_children(data));//not builtins
}