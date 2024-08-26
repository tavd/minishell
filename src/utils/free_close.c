/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:17 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/23 18:34:30 by tavdiiev         ###   ########.fr       */
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
			restore_stdin_stdout_close_copies(cmd_list->io);
	}
	close_pipe_fds(cmd_list, NULL);
}

// void	free_data(t_data *data)
// {
// 	if (data && data->user_input)
// 	{
// 		free_ptr(data->user_input);
// 		data->user_input = NULL;
// 	}
// 	if (data && data->cmd)
// 		lst_clear_cmd(&data->cmd, &free_ptr);
// }

// void	lst_delone_cmd(t_command *lst, void (*del)(void *))
// {
// 	if (lst->name)
// 		(*del)(lst->name);
// 	if (lst->args)
// 		free_str_tab(lst->args);
// 	if (lst->pipe_fd)
// 		(*del)(lst->pipe_fd);
// 	if (lst->io)
// 		free_io(lst->io);
// 	(*del)(lst);
// }

// void	lst_clear_cmd(t_command **lst, void (*del)(void *))
// {
// 	t_command	*temp;

// 	temp = NULL;
// 	while (*lst != NULL)
// 	{
// 		temp = (*lst)->next;
// 		lst_delone_cmd(*lst, del);
// 		*lst = temp;
// 	}
// }