/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:35:38 by irsander          #+#    #+#             */
/*   Updated: 2023/10/10 16:53:32 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	dest_i;
	size_t	src_i;
	size_t	i;

	dest_i = ft_strlen(dest);
	src_i = ft_strlen(src);
	if (dest_i >= destsize)
		return (destsize + src_i);
	i = 0;
	while (src[i] && dest_i < (destsize -1))
		dest[dest_i++] = src[i++];
	dest[dest_i] = '\0';
	return (dest_i - i + src_i);
}

// int main(void)
// {
//     char s [] = "goodbye";
//     char d [] = "hello";
//     char s2 [] = "goodbye";
//     char d2 [] = "hello";

//     ft_strlcat(d, s, sizeof(d));
//     printf("%s\n", d);

//     strlcat(d2, s2, sizeof(d2));
//     printf("%s\n", d2);
// }