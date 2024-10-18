/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:22:59 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:21:12 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	*ft_memset(void *block, int c, size_t size)
{
	const unsigned char	value = (unsigned char)c;
	unsigned char		*ptr;

	ptr = block;
	while (size--)
	{
		*ptr++ = value;
	}
	return (block);
}
	//if (!block)
	//	return (block);
// sloW!

// int main()
// {
//     int size = 5;
//     char c  = 'r';
//     int *ptr = malloc(size);
//     memset(ptr, c, size);

//     int *p = malloc(size);
//     ft_memset(p, c, size);

//     int i = 0;
//     while (i++ < size)
//     {
//         printf("%c", *ptr);
//     }
//     i = 0;
//     printf("\n");
//     while (i++ < size)
//     {
//         printf("%c", *p);
//     }
//     return 0;
// }
