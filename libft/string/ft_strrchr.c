/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:24:51 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/23 21:57:52 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	val = (const char)c;
	size_t		len;

	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len] == val)
			return ((char *)str + len);
		len--;
	}
	if (str[len] == val)
		return ((char *)str + len);
	return (NULL);
}

/*
 int main()
 {
 	char *s = "bonjourno";
 	char look = 'b';
 	char *p = strrchr(s, look);

 	printf("re:%s\n", p);
 	printf("re:%p, %p\n",s, p);
 	p = ft_strrchr (s, look);
 	printf("my:%s\n", p);
 	printf("re:%p, %p",s, p);

 	return 0;
  }
*/
