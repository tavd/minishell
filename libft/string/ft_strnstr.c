/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:24:41 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/30 18:28:58 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

/*
 @needle: null terminated string
 @haystack: string
 @len: length of the haystack that is being searched for

 function returns:
	- haystack if length of needle is 0.
	- first occurence of needle in haystack if it is found.
	- NULL if needle is not found
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const size_t	needle_len = ft_strnlen(needle, len);
	const char		*end_haystack = ft_strnlen(haystack, len) - needle_len);

	if (needle_len == 0)
		return ((char *)haystack);
	while (*haystack && haystack <= end_haystack)
	{
		if (haystack[0] == needle[0] && \
			(needle_len == 1 || ft_strncmp(haystack, needle, needle_len) == 0))
			return ((char *)haystack);
		else
			++haystack;
	}
	return (NULL);
}

// #include <stdio.h>
//
//  int main()
//  {
// 	char haystack[30] = "aaabcabcd";
// 	char needle[10] = "aabc";
//  	char *ptr;
// 	int len = -1;
//  	ptr = strnstr(haystack, needle, len);
//  	printf("real:%s\n", ptr);
//  	ptr = ft_strnstr(haystack, needle, len);
//  	printf("mine:%s", ptr);
//
//  	return 0;
//  }
