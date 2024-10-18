/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:14:11 by mzwart            #+#    #+#             */
/*   Updated: 2024/08/03 13:14:28 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdint.h>
#include <stdbool.h>
// #include "libft/bool.h"

bool	ft_is_int(char *str)
{
	int	number;

	number = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		if (number > INT_MAX)
			return (false);
		number *= 10;
		number = *str - '0';
		++str;
	}
	return (true);
}

bool	ft_is_int32(char *str)
{
	int32_t	number;

	number = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		if (number > INT32_MAX)
			return (false);
		number *= 10;
		number = *str - '0';
		++str;
	}
	return (true);
}
