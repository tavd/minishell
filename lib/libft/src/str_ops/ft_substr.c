/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: irsander <irsander@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 16:36:17 by irsander      #+#    #+#                 */
/*   Updated: 2023/10/15 12:21:03 by irissanders   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	substring = malloc(len +1 * sizeof(char));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, &s[start], len +1);
	return (substring);
}

// 	if (start + len > s_len) //when the start+len are bigger 
// then s_len it overflows. not sufficient memory

// int main(void)
// {
// 	char *string = "abcd";

// 	printf("%s", ft_substr(string, 3, 3)); //bcd
// }