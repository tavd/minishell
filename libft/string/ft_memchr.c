/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:34:09 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:20:27 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	char_we_looking_for = (unsigned char)c;
	unsigned char		*str;

	str = (unsigned char *)s;
	while (n > 0)
	{
		if (*str == char_we_looking_for)
			return ((void *)str);
		str++;
		n--;
	}
	return (NULL);
}

// int main()
// {
// 	char *s1 = "abcd";
// 	printf("%s\n", (char *)memchr(s1, 'd', 4));
// 	printf("%s", (char *)ft_memchr(s1,'d', 4));
// 	return 0;
// }
