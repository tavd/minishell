/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:22:59 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:20:59 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	const unsigned char	*src_ptr;
	unsigned char		*dest_ptr;

	if (!dest && !src && size > 0)
		return (dest);
	src_ptr = (unsigned char *)src;
	dest_ptr = (unsigned char *)dest;
	if (src >= dest)
		while (size--)
			*dest_ptr++ = *src_ptr++;
	else
	{
		dest_ptr += size;
		src_ptr += size;
		while (size--)
			*--dest_ptr = *--src_ptr;
	}
	return (dest);
}

/*
 int main()
 {
 	char s[7] = "abcdef";
 	char s1[7] = "abcdef";
 	printf("%s\n", s);
	memmove(s + 6, s 10);
 	ft_memmove(s1 + 6, s1 ,10);
 	printf("%s\n", s);
 	return 0;
}
*/
