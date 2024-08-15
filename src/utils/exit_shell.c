#include "../../incl/minishell.h"

void	exit_shell(t_data *data, int exit_number)
{
	if (data)
	{
		if (data->cmd && data->cmd->io)
			close_fds(data->cmd, true);
		//free_data(data, true);
	}
	printf("the end of exit shell\n");
	exit(exit_number);
}