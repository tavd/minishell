/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavdiiev <tavdiiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:17 by tavdiiev          #+#    #+#             */
/*   Updated: 2024/07/13 20:09:33 by tavdiiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			if (arr[i])
			{
				free_ptr(arr[i]);
				arr[i] = NULL;
			}
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

