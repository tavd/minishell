/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:23:49 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:23:58 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	const size_t	len_src = ft_strlen(src);
	size_t			len_dest;

	len_dest = 0;
	while (*dest)
	{
		len_dest++;
		dest++;
	}
	if (size <= len_dest)
		return (size + len_src);
	size = size - len_dest - 1;
	while (*src && size > 0)
	{
		*dest++ = *src++;
		size--;
	}
	*dest = '\0';
	return (len_dest + len_src);
}

	//if (!dest)
	//	return (len_src);
/*
int main()
	{
	char *src = "bc";
	char p[6] = "abcda";

	size_t ret = ft_strlcat(p, src, 5);
	//ft_strlcat(p, src, 5);
	printf("%zu ; %s",ret,  p);
	return 0;
}
*/

/*
int main ()
{
	char d1[20] = "rrrrr";
	d1[5] = 'r';
	char d2[20] = "lorem";
	d2[5] = 'r';
	char a1[20] = "rrrrr";
	a1[5] = 'r';
	char a2[20] = "lorem";
	a2[5] = 'r';
	// char c[1] = "\0";
	int size = 15;
	int x = strlcat(a1, a2, size);
	printf("re: %s\n", a1);
	printf("re return:%d \n", x);

	int y = ft_strlcat(d1, d2, size);
	printf("my: %s\n", d1);
	printf("my return:%d \n", y);
	//printf("huu%lu", sizeof(d1));
	///printf("m:%u\n" , ft_strlcat(s1, str2, size));
	//printf("real:%s\n",s);
	//printf("mine:%s", s1);

	return 0;
}
*/
