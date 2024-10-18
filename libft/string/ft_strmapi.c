/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:24:22 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/30 18:17:03 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
/*
char add_index(unsigned int index, char c)
{
	return (c + index);
}
*/
char	*ft_strmapi(const char *str, char (*function)(unsigned int, char))
{
	const size_t	str_len = ft_strlen(str);
	char			*new_str;
	unsigned int	i;

	if (!str || !function)
		return (NULL);
	i = 0;
	new_str = (char *)malloc(str_len + 1);
	if (!new_str)
		return (NULL);
	new_str[str_len] = '\0';
	while (i < str_len)
	{
		new_str[i] = function(i, str[i]);
		++i;
	}
	return (new_str);
}

/*
int main ()
{
	char *s = NULL;
	char *y = ft_strmapi(s, add_index);

	printf("%s", y);

	return 0;
}
*/
