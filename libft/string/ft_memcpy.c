/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:22:59 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:20:21 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

	//if ((!dest || !src)
	//	return (dest);
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	if (!dest && !src && n > 0)
		return (dest);
	while (n--)
	{
		*dest_ptr = *src_ptr;
		src_ptr++;
		dest_ptr++;
	}
	return (dest);
}

/*
#include <stdlib.h>
int main()
{
	char s[8] = "ABC";
	char p[8];

	ft_memcpy(p, s, 4);
	printf("%s", p);
	return 0;
}
*/
