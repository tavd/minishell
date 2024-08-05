#include "../../incl/minishell.h"

//Checks if the command is a directory rather than an executable.
bool	command_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

int	is_command_not_found(t_data *data, t_command *command)
{
	if (!ft_strchr(command->name, '/') 
		&& get_env_index(data->env, "PATH") != -1)
		return (error_msg_command(command->name, NULL, "command not found", 
				CMD_NOT_FOUND));
	if (access(command->name, F_OK) != 0)//check for file existence
		return (error_msg_command(command->name, NULL, strerror(errno), CMD_NOT_FOUND));
	else if (command_is_dir(command->name))
		return (error_msg_command(command->name, NULL, "Is a directory", CMD_NOT_EXECUTABLE));
	else if (access(command->name, F_OK | X_OK) != 0)
		return (errmsg_cmd(command->name, NULL, strerror(errno),
				CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}