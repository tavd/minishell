#include "../../incl/minishell.h"

void	exit_shell(t_data *data, int exit_number)
{
	if (data)
	{
		if (data->cmd && data->cmd->io)
			close_fds(data->cmd, true);
		//free_data(data, true);
	}
	exit(exit_number);
}