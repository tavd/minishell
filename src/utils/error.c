/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:15:38 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/07/17 18:44:18 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static	bool is_export(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0)
		return (true);
	return (false);
}

int	error_msg_command(char *command, char *detail, char *error_message, int error_number)
{
	char *message;
	int	add_quotes;

	add_quotes = is_export(command);
	message = ft_strdup("minishell: ");
	if (command)
	{
		message = ft_strjoin(message, command);
		message = ft_strjoin(message, ": ");
	}
	if (detail)
	{
		if (add_quotes)
			message = ft_strjoin(message, "`");
		message = ft_strjoin(message, detail);
		if (add_quotes)
			message = ft_strjoin(message, "'");
		message = ft_strjoin(message, ": ");	
	}
	message = ft_strjoin(message, error_message);
	ft_putendl_fd(message, STDERR_FILENO);
	free_ptr(message);
	return (error_number);
}
