/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:54:44 by mzwart            #+#    #+#             */
/*   Updated: 2024/11/18 15:54:44 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strnlen(const char *str, size_t max_len)
{
	const char	*str_origin = str;

	while (*str && (str_origin - str) < max_len)
		++str;
	return (str - str_origin);
}
