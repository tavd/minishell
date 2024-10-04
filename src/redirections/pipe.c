/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:03:51 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/10/04 15:53:14 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	create_pipes(t_data *data)
{
	t_command	*curr_command;

	curr_command = data->cmd;
	printf("in create_pipes\n");
	while (curr_command)
	{
		printf("in while create pipes\n");
		printf("curr_command->name=%s\n", curr_command->name);
		if (curr_command->next)
		{
			printf("in if create pipes\n");
			curr_command->pipe_fd = malloc(sizeof(*curr_command->pipe_fd) * 2);
			if (!curr_command->pipe_fd || pipe(curr_command->pipe_fd) != 0)
			{
			// 	free_data(data, false);//todo
				return (false);
			}
		}
		curr_command = curr_command->next;
	}
	printf("the end of create_pipes\n");
	return (true);
}

void	close_pipe_fds(t_command *cmds, t_command *this_cmd)
{
	while (cmds)
	{
		if (cmds != this_cmd && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

bool	redirect_io_pipe(t_command *cmds, t_command *this_cmd)
{
	printf("in redirect_io_pipe\n");
	if (!this_cmd)
		return (false);
	if (this_cmd->prev && this_cmd->prev->is_piped)
		dup2(this_cmd->prev->pipe_fd[0], STDIN_FILENO);//Redirect stdin to pipe read end
	if (this_cmd->is_piped)//if (this_cmd->next)?
		dup2(this_cmd->pipe_fd[1], STDOUT_FILENO);//Redirect stdout to pipe write end		
	close_pipe_fds(cmds, this_cmd);
	printf("the end of redirect_io_pipe\n");
	return (true);
}
