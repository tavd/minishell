/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:30:21 by irsander          #+#    #+#             */
/*   Updated: 2024/08/10 21:01:03 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_cmd(t_command **cmd)
{
	(*cmd)->name = NULL;
	(*cmd)->path = NULL;
	(*cmd)->args = NULL;
	(*cmd)->is_piped = false;
	(*cmd)->pipe_fd = 0;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

t_command	*lst_new_cmd(bool value)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!(new_node))
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_command));
	new_node->is_piped = value;
	// initialize_cmd(&new_node);
	return (new_node);
}

void	lst_add_back_cmd(t_command **alst, t_command *new_node)//new_node=lst_new_cmd
{
	t_command	*start;

	start = *alst;
	if (start == NULL)
	{
		*alst = new_node;
		return ;
	}
	if (alst && *alst && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

t_command	*get_last_cmd(t_command *cmd)
{
	printf("get_last_cmd\n");
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
static void	open_infile(t_io *io, char *file_name)
{
	io->infile_name = file_name;
		if (io->infile_name && io->infile_name[0] == '\0')
	{
		error_msg_command(file_name, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_infile = open(io->infile_name, O_RDONLY);
	if (io->fd_infile == -1)
	{
		printf("in open infile\n");
		error_msg_command(io->infile_name, NULL, strerror(errno), false);	
	}
}
int main(int argc, char **argv, char **envp)
{
    t_data data;
	// (void)argv;
ft_memset(&data, 0, sizeof(t_data));
if (!init_data(&data, envp))
exit_shell(NULL, EXIT_FAILURE);
	
	// 		printf("command.io=%p\n", command.io);
	//printf("res=%d\n", execute_command(&data, &command));
	lst_add_back_cmd(&data.cmd, lst_new_cmd(false));
	data.cmd->argc = argc;
	char *command_args[] = {argv[1], argv[2], NULL};
		data.cmd->args = command_args;//malloc(sizeof * args * 2);
		data.cmd->args[0] = command_args[0]; //ft_strdup(args[0]);
		data.cmd->args[1] = command_args[1];//NULL;
		data.cmd->name = command_args[0];
	t_command *command;
	command = get_last_cmd(data.cmd);
	init_io(command);
	open_infile(command->io, "infie");
	printf("main: execute=%d\n", execute(&data));
	printf("data.cmd->path=%s\n", data.cmd->path);
	// pwd(&data);
	// int i = 0;
	// 	while (data.env[i])
	// ft_putendl_fd(data.env[i++], STDOUT_FILENO);
    return (0);
}