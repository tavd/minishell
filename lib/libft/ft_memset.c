/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:35:18 by irsander          #+#    #+#             */
/*   Updated: 2023/10/10 16:51:35 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = ((unsigned char)c);
	return (s);
}

// int main(void)
// {
//     char str[] = "hellogoodbye";

//     printf("%s\n", (char *)ft_memset(str, '$', 5));
//     printf("%s\n", (char *)memset(str, '$', 5));
// }