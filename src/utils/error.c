/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:15:38 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/10/05 20:20:03 by tavdiiev         ###   ########.fr       */
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
	free(message);
	return (error_number);
}

bool	usage_message(bool return_val)
{
	ft_putendl_fd("Usage: ./minishell", 2);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", 2);
	return (return_val);
}
