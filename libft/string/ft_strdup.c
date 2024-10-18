/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:22:31 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/23 21:56:35 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*ft_strdup(const char *str)
{
	size_t	str_len;
	char	*cpy;

	str_len = ft_strlen(str) + 1;
	cpy = (char *)malloc(str_len);
	if (cpy == NULL)
		return (NULL);
	ft_memcpy(cpy, str, str_len);
	return (cpy);
}

/*
#include <string.h>
#include <assert.h>
 
int main(void)
{
    const char *s1 = "String";
    char *s2 = ft_strdup(s1);
    assert(strcmp(s1, s2) == 0);
    free(s2);
}

 #include <bsd/string.h>

 int main()
 {
 	char *s = "abc";
 	char *c	= strdup(s);


	printf("%s\n", c);	
	printf("%s", 	ft_strdup(s));
 

 	return 0;
 }
 */
