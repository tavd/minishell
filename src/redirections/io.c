/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:37:08 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/08 20:23:49 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	is_valid_fd(t_io *io)
{
	if (!io || (!io->infile_name && !io->outfile_name))
		return(true);
	if ((io->infile_name && io->fd_in == -1) 
		|| (io->outfile_name && io->fd_out == -1))
		return(false);
	return(true);
}

bool	redirect_io_file(t_io *io)
{
	int	status;

	printf("in redirect_io_file\n");
	status = true;
	if (!io)
		return (status);
	io->stdin_copy = dup(STDIN_FILENO);
	if (io->stdin_copy == -1)
		status = error_msg_command("dup", "stdin_copy", strerror(errno), false);
	io->stdout_copy = dup(STDOUT_FILENO);
	if (io->stdout_copy == -1)
		status = error_msg_command("dup", "stdout_copy", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			status = error_msg_command("dup2", io->infile_name, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			status = error_msg_command("dup2", io->outfile_name, strerror(errno), false);
	printf("in redirect_io_file end\n");
	return (status);
}

//Restore stdin and stdout to their original fds 0 and 1.
bool	restore_stdin_stdout(t_io *io)
{
	int	status;

	printf("in restore_stdin\n");
	status = true;
	if (!io)
		return (status);
	if (io->stdin_copy != -1)
	{
		if (dup2(io->stdin_copy, STDIN_FILENO) == -1)
			status = false;
		close(io->stdin_copy);
		io->stdin_copy = -1;
	}
	if (io->stdout_copy != -1)
	{
		if (dup2(io->stdout_copy, STDOUT_FILENO) == -1)
			status = false;
		close(io->stdout_copy);
		io->stdout_copy = -1;
	}
	return (status);
}