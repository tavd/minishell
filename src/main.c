/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:30:21 by irsander          #+#    #+#             */
/*   Updated: 2024/08/17 20:29:57 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*lst_new_cmd(bool value)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!(new_node))
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_command));
	new_node->is_piped = value;
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

void	open_infile(t_io *io, char *file_name)
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

void	open_outfile(t_io *io, char *file_name)
{
	io->outfile_name = file_name;
	if (io->outfile_name && io->outfile_name[0] == '\0')
	{
		error_msg_command(file_name, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_outfile = open(io->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_outfile == -1)
		error_msg_command(io->outfile_name, NULL, strerror(errno), false);
}

void	add_pipe(t_command **cmd)
{
	t_command	*last_cmd;

	last_cmd = get_last_cmd(*cmd);
	last_cmd->is_piped = true;
}

int main(int argc, char **argv, char **envp)
{
	t_data data;
	ft_memset(&data, 0, sizeof(t_data));

	if (!init_data(&data, envp))
		exit_shell(NULL, EXIT_FAILURE);
	(void)argc;
// ./minishell infile grep li grep li outfile or ./minishell grep li grep li grep li
//if stdout was redirected to a pipe (pipe_fd[0]) all the following printfs go to the pipe read end
//./minishell env grep i we can see some of printf output
	// Add first command (ls -a)
	t_command *cmd1 = lst_new_cmd(false);
	//cmd1->argc = 3; //for testing a single comand with variable number of arguments: argc - 1 (echo, export);
	//printf("cmd1->argc=%d\n", cmd1->argc);//4
	cmd1->args = malloc(3 * sizeof(char*));
	init_io(cmd1);
	// open_infile(cmd1->io, "infile");//argv[1]

	//-------test env --------------------
	cmd1->args[0] = argv[1];
	cmd1->args[1] = NULL;
	//-------test commands with 2 args----------------------------
	// cmd1->args[0] = argv[1]; // "ls"
	// cmd1->args[1] = argv[2]; // "-a"
	// cmd1->args[2] = NULL;
	//-------test echo------------------------------------------
	// int i = 0;
	// while (i < argc - 1)
	// {
	// 	cmd1->args[i] = argv[i + 1];
	// 	printf("args=%s ", cmd1->args[i]);
	// 	i++;
	// }
	// cmd1->args[i] = NULL;
	cmd1->name = argv[1];
	lst_add_back_cmd(&data.cmd, cmd1);
//---------------2nd command-----------------------------------
	// // // if (argv[3])
	// add_pipe(&data.cmd);

	// t_command *cmd2 = lst_new_cmd(false);
	// // int cmd2_start = cmd1->argc + 1;
    // //cmd2->argc = 3; //argc - cmd2_start;
	// // printf("cmd2->argc=%d\n", cmd2->argc);//2//
	// cmd2->args = malloc(3 * sizeof(char*));
	// init_io(cmd2);

	// cmd2->args[0] = argv[2]; //argv[3]; // "grep"
	// cmd2->args[1] = argv[3];//argv[4]; // "i"
	// cmd2->args[2] = NULL;
	// // // i = 0;
	// // // while (i < cmd2->argc)
	// // // {
	// // // 	cmd2->args[i] = argv[i + 2];//./minishell env grep ^PATH
	// // // 	i++;
	// // // }
	// // // cmd2->args[i] = NULL;
	// cmd2->name = argv[2];
	// // if (cmd2->args[0])
	// lst_add_back_cmd(&data.cmd, cmd2);
//-------------------3rd command----------------------------------
	// add_pipe(&data.cmd);

	// t_command *cmd3 = lst_new_cmd(false);
	// cmd3->argc = 3;
	// cmd3->args = malloc(3 * sizeof(char*));
	// init_io(cmd3);
	// cmd3->args[0] = argv[4]; // "grep"
	// cmd3->args[1] = argv[5]; // "i"
	// cmd3->args[2] = NULL;
	// cmd3->name = argv[4];
	// lst_add_back_cmd(&data.cmd, cmd3);
	// open_outfile(cmd2->io, "outfile");
	// printf("argv[5]=%s\n", argv[5]);
//-------------------------------------------------------
	printf("Executing commands:\n");
	t_command *current_cmd = data.cmd;
	while (current_cmd != NULL) {
		printf("Command: %s\n", current_cmd->name);
		printf("Is Piped: %d\n", current_cmd->is_piped);
		current_cmd = current_cmd->next;
	}
	printf("main: execute = %d\n", execute(&data));
	pwd(&data);//for cd
// 	i = 0;
// 	while (data.env[i])
// ft_putendl_fd(data.env[i++], STDOUT_FILENO);
    return (0);
}