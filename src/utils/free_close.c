/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:17 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/10 18:26:26 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			if (arr[i])
			{
				free_ptr(arr[i]);
				arr[i] = NULL;
			}
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	close_fds(t_command *cmd_list, bool close_copies)
{
	if (cmd_list->io)
	{
		if (cmd_list->io->fd_infile != -1)
			close(cmd_list->io->fd_infile);
		if (cmd_list->io->fd_outfile != -1)
			close(cmd_list->io->fd_outfile);
		if (close_copies)
			restore_stdin_stdout(cmd_list->io);
	}
	close_pipe_fds(cmd_list, NULL);
}
