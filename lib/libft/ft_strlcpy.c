/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:35:44 by irsander          #+#    #+#             */
/*   Updated: 2023/10/10 16:53:42 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;

	i = 0;
	if (destsize == 0)
		return (ft_strlen(src));
	while (i < (destsize -1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

// int main(void)
// {
//     char s [] = "goodbye";
//     char d [] = "hello";
//     char s2 [] = "goodbye";
//     char d2 [] = "hello";

//     ft_strlcpy(d, s, sizeof(d));
//     printf("%s\n", d);

//     strlcpy(d2, s2, sizeof(d2));
//     printf("%s\n", d2);
// }