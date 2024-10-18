/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:19:59 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:20:08 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	ft_memcmp(const void *block1, const void *block2, size_t n)
{
	const unsigned char	*ptr1 = block1;
	const unsigned char	*ptr2 = block2;
	size_t				i;

	if (!n)
		return (0);
	i = 0;
	while (i < (n - 1) && (ptr1[i] == ptr2[i]))
		++i;
	return (ptr1[i] - ptr2[i]);
}

/*
int main()
{
	char *s1 = "abcdsdef";
	char *s2 = "abcdefgh";

	int n = 0;
	while (n < 10)
	{
		printf("s:%i ", ft_memcmp(s1, s2, n));
		printf("H:%i\n", memcmp(s1, s2, n));
		n++;
	}

	return 0;
}
*/
/*
int main()
{
	int n = 4;
	char *s = "abc";
	char *a = "abc";
	//a[2] = '\0';
	printf("%d\n", memcmp(s, a, n));
	printf("%d\n", ft_memcmp(s, a, n));

	return 0;
}

int	main(int argc, char *argv[])
{
	char *str;
	char *str2;
	if (argc == 3)
	{
	char *str = argv[1];
	char *str2 = argv[2];
 
	char a[10] = "abcag32";
	char b[10] = "abcag32";
	printf("%d\n", ft_strcmp(str,str2) );
	printf("%d", strcmp(str, str2));
	}
	return 0;
}
*/
