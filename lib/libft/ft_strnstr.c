/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:36:03 by irsander          #+#    #+#             */
/*   Updated: 2023/11/07 15:19:50 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len && (needle_len + i <= len))
	{
		if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

// while (haystack[i] && i < len && (needle_len + i <= len)) 
// laatste voor overflow
// int main(void)
// {
//     const char *haystack;
//     const char *needle;

//     haystack = "MZIRIBMZIRIBMZE123";
//     needle = "MZIRIBMZE";
//     printf("%s\n", ft_strnstr(haystack, needle, ft_strlen(needle)));
// }