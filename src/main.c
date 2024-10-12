/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:30:21 by irsander          #+#    #+#             */
/*   Updated: 2024/10/12 17:41:28 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	g_last_exit_code;
// static bool	start_check(t_data *data, int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	// if (ac != 1 && ac != 3)
// 	// 	return (usage_message(false));
// 	// if (ac == 3)
// 	// {
// 	// 	data->interactive = false;
// 	// 	if (!av[1] || (av[1] && ft_strncmp(av[1], "-c", 2) != 0))
// 	// 		return (usage_message(false));
// 	// 	// else if (!av[2] || (av[2] && av[2][0] == '\0'))//bash -c "" returns a prompt, no usage message
// 	// 	// 	return (usage_message(false));
// 	// }
// 	// else
// 		data->interactive = true;
// 	return (true);
// }

t_command	*lst_new_cmd(bool value)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(*new_node));
	if (!(new_node))
		return (NULL);
	ft_memset(new_node, 0, sizeof(*new_node));
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
	while (cmd->next != NULL)//segfault
	{
		printf("get_last\n");
		cmd = cmd->next;		
	}
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

void	lst_delone_cmd(t_command *lst, void (*del)(void *))
{
	if (lst->name)
		(*del)(lst->name);
	if (lst->args)
		free_char_arr(lst->args);
	// if (lst->pipe_fd)
	// 	(*del)(lst->pipe_fd);
	// if (lst->io)
	// 	free_io(lst->io);
	(*del)(lst);
}

void	lst_clear_cmd(t_command **lst, void (*del)(void *))
{
	t_command	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		lst_delone_cmd(*lst, del);
		*lst = temp;
	}
}

// void	free_data(t_data *data)
// {
// 	if (data && data->user_input)
// 	{
// 		free(data->user_input);
// 		data->user_input = NULL;
// 	}
// 	if (data && data->cmd)
// 		lst_clear_cmd(&data->cmd, &free_ptr);
// }

void lst_add_front_cmd(t_command **list, t_command *cmd1)
{
	cmd1->next = *list;
	*list = cmd1;
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    (void)argc;
	(void)argv;

    ft_memset(&data, 0, sizeof(data));
    if (!init_data(&data, envp))
        exit_shell(NULL, EXIT_FAILURE);
    while (1)
	{
        data.user_input = readline(PROMPT);
		printf("data.user_input = %s\n",  data.user_input);
		char **input_strings = ft_split(data.user_input, ' ');
        t_command *cmd1 = lst_new_cmd(false);
		// printf("data=%p\ndata.cmd=%p\n", &data, data.cmd);
		cmd1->args = input_strings;
		init_io(cmd1);
		lst_add_front_cmd(&data.cmd, cmd1);

		// lst_add_back_cmd(&data.cmd, cmd1);
		cmd1->name = cmd1->args[0];
		// open_outfile(cmd1->io, "outfile");
	
	// printf("cmd1->args[0]=%s\n", cmd1->args[0]);
	// printf("cmd1->args[2]=%s\n", cmd1->args[2]);
	// int i = 0;
	// while (cmd1->args[i])
// printf("cmd1->args=%s ", cmd1->args[i++]);
// printf("\n");
// 	  free(data.user_input);
// 		printf("data.cmd->name=%s\n", data.cmd->name);
// 	//------------------command2-------------------
	// add_pipe(&data.cmd);
	// t_command *cmd2 = lst_new_cmd(false);
	// cmd2->args = &input_strings[2];
    // lst_add_front_cmd(&data.cmd, cmd2);//need to add back
	// init_io(cmd2);
	//  cmd2->name = cmd2->args[0];
//         // printf("Command: %s\n", data.cmd->name);
//         // printf("Is Piped: %d\n", data.cmd->is_piped);
// 	int i = 0;
// 	printf("cmd2->args=%s ", cmd2->args[i++]);
// printf("\n");
// 	printf("cmd2->args[0]=%s\n", cmd2->args[0]);
// 	printf("cmd2->args[1]=%s\n", cmd2->args[1]);
	//-------------------if added back------------------------
		// 	t_command *current_cmd = data.cmd;
		// 	t_command *cur2 = current_cmd;
		// 	if (current_cmd)
		// 	{
		// printf("Command: %s\n", current_cmd->name);
		// printf("Is Piped: %d\n", current_cmd->is_piped);
		// 	   if (execute(&data) == -1)
    	//         printf("Command execution failed\n");		
		// 	current_cmd = current_cmd->next;
		// 	free(cur2->name);
		// 	}
				if (execute(&data) == -1)
    	        printf("Command execution failed\n");
			free(data.cmd->name);
        // free(data.user_input);
		// printf("data.cmd->name=%s\n", data.cmd->name);

		
		// data.cmd->name = NULL;


		
		// if (cmd1->args)
		// free_str_arr(cmd1->args);
		// free_str_arr(input_strings);
		// free_data(&data);

	
    }

    return 0;
}