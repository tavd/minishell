/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:30:21 by irsander          #+#    #+#             */
/*   Updated: 2024/08/09 18:44:01 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_cmd(t_command **cmd)
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
	initialize_cmd(&new_node);
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


int main(int argc, char **argv, char **envp)
{
    t_data data;
	// (void)argv;
ft_memset(&data, 0, sizeof(t_data));
if (!init_data(&data, envp))
exit_shell(NULL, EXIT_FAILURE);
	t_command command;
	init_io(&command);
	//printf("res=%d\n", execute_command(&data, &command));
	lst_add_back_cmd(&data.cmd, lst_new_cmd(false));
	data.cmd->argc = argc;
	char *command_args[] = {argv[1], argv[2], NULL};
		data.cmd->args = command_args;//malloc(sizeof * args * 2);
		data.cmd->args[0] = command_args[0]; //ft_strdup(args[0]);
		data.cmd->args[1] = command_args[1];//NULL;
		data.cmd->name = command_args[0];
	printf("res=%d\n", execute(&data));
	// pwd(&data);
	// int i = 0;
	// 	while (data.env[i])
	// ft_putendl_fd(data.env[i++], STDOUT_FILENO);
    return (0);
}