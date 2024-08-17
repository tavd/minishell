/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:07:52 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/08/17 19:58:54 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void update_working_dirs(t_data *data, char *current_working_dir)
{
	set_env(data, "OLDPWD", get_env_value(data->env, "PWD"));
	set_env(data, "PWD", current_working_dir);
	if (data->old_working_dir)
	{
		free_ptr(data->old_working_dir);
		data->old_working_dir = ft_strdup(data->working_dir);
	}
	if (data->working_dir)
	{
		free_ptr(data->working_dir);
		data->working_dir = ft_strdup(current_working_dir);
	}
	free_ptr(current_working_dir);
}

/*
*	chdir can sometimes set errno to ESTALE ("Stale file handle")
*	when a parent directory is removed on some systems. This is due
*	to the inode table entry being recycled. This is a fix to display
*	"no such file or directory" error instead.
*/
static	int	chdir_error_msg(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	error_msg_command("cd", path, strerror(errno), errno);
	return (EXIT_FAILURE);
}

static	int change_directory(t_data *data, char *path)
{
	char	*tmp;
	char	buf[PATH_MAX];
	char	*current_working_dir;

	if (chdir(path) != 0)
		return (chdir_error_msg(path));
	current_working_dir = getcwd(buf, PATH_MAX);
	printf("change_directory: cwd=%s\n", current_working_dir);
	if (!current_working_dir)
	{
		error_msg_command("cd: error retrieving current directory",
	"getcwd: cannot access parent directories",
	strerror(errno), errno);
	if (path[0] == '/')
    	current_working_dir = ft_strdup(path);
	else
	{
		current_working_dir = ft_strjoin(data->working_dir, "/");
		tmp = current_working_dir;
		current_working_dir = ft_strjoin(tmp, path);//previous_directory/new_path
		free_ptr(tmp);
	}
	}
	else
		current_working_dir = ft_strdup(buf);
	update_working_dirs(data, current_working_dir);
	return (EXIT_SUCCESS);
}

int	cd(t_data *data, char ** args)
{
	char	*path;

printf("in cd\n");
printf("args[1]=%s\n", args[1]);
	if (!args || !args[1] || ft_strncmp(args[1], "--", 3) == 0)
	{
		printf("here!!!!!!\n");
		path = get_env_value(data->env, "HOME");
		if (!path || path[0] == '\0' || path[0] == ' ')
			return (error_msg_command("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (change_directory(data, path));
	}
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_value(data->env, "OLDPWD");
		if (!path || path[0] == '\0' || path[0] == ' ')
			return (error_msg_command("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (change_directory(data, path));
	}
	if (args[2])
		return (error_msg_command("cd", NULL, "too many arguments", EXIT_FAILURE));
			printf("end of cd\n");
	return (change_directory(data, args[1]));
}

