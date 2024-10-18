/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:24:16 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:24:17 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	str_len;

	str_len = 0;
	if (!str)
		return (str_len);
	while (*str++)
		str_len++;
	return (str_len);
}

	//if (!str)
	//	return (str_len);
// int main ()
// {
// 	char *word = "123456789";
// 	int x = ft_strlen(word);
// 	printf("%d", x);
// 	return 0;
// }
