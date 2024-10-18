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

#include "libft/libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	const size_t	needle_len = ft_strlen(needle);
	const size_t	hay_len = len * (ft_strlen(hay) > len)
		+ ft_strlen(hay) * (ft_strlen(hay) <= len);
	char			*end_hay;

	if (!needle_len)
		return ((char *)hay);
	end_hay = (char *)hay + hay_len - needle_len;
	while (hay <= end_hay)
	{
		if (*hay == *needle && ft_strncmp(hay, needle, needle_len) == 0)
			return ((char *)hay);
		else
			hay++;
	}
	return (NULL);
}

/*
 int main()
 {
	char hay[30] = "aaabcabcd";
	char needle[10] = "aabc";
 	char *ptr;
	int len = -1;
 	ptr = strnstr(hay, needle, len);
 	printf("real:%s\n", ptr);
 	ptr = ft_strnstr(hay, needle, len);
 	printf("mine:%s", ptr);

 	return 0;
 }
*/
