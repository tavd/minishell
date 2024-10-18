/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:22:08 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:22:16 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*ft_strchr(const char *str, int c)
{
	const char	char_we_looking_for = (const char)c;

	while (*str != '\0')
	{
		if (*str == char_we_looking_for)
			return ((char *)str);
		str++;
	}
	if (*str == char_we_looking_for)
		return ((char *)str);
	return (NULL);
}

/*
int main()
{
	char *s = "avc";
	char *p = strchr(s, 'a');
	printf("%s\n", p);
	p = ft_strchr (s, 'a');
	printf("%s\n", p);
	unsigned char val = (unsigned char)2423;

	printf("%c", val);

	return 0;
}
*/
