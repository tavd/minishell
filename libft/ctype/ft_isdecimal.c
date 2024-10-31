/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdecimal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:02:25 by mzwart            #+#    #+#             */
/*   Updated: 2024/08/08 16:10:47 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	ft_isdecimal(const char *nptr)
{
	bool	dot;

	dot = false;
	if (*nptr == '-')
		++nptr;
	while (*nptr)
	{
		if (!dot && *nptr == '.')
			dot = true;
		else if (ft_isdigit(*nptr))
			;
		else
			return (false);
		++nptr;
	}
	return (true);
}
