/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:22:59 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/30 15:26:22 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < (size - 1))
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

/*
int main()
{
	char s1[10];
	char s2[10];
	// printf("%p\n", s1);
	// printf("%p\n", s2);

	size_t size = 3;
	char *src = "----";
	size_t r1 = ft_strlcpy(s1, src, size);
	size_t r2 = strlcpy(s2, src, size);
	printf("\nmine:%s", s1);
	printf("%zu", r1);
	printf("\nreal:%s", s2);
	printf("%zu", r2);

	return 0;
}
*/
