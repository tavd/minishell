/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:15:51 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/30 15:26:43 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			++i;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

/*
int	main(int argc, char *argv[])
{
	char *str;
	char *str2;
	int size;
	str = "abcdef";
	str2 = "abcdwx";
	size = 4;
	printf("mine:%d\n", ft_strncmp(str, str2, size) );
	printf("real:%d", strncmp(str, str2, size));
	return 0;
}
*/
