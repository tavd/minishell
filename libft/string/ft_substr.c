/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:25:01 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:25:02 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t max_substr_len)
{
	char	*substr;
	size_t	sub_len;
	size_t	index;

	if (!s)
		return (NULL);
	index = 0;
	sub_len = 0;
	while (s[index] != '\0' && index < start)
		index++;
	if (index == start)
		while (s[index + sub_len] != '\0' && sub_len < max_substr_len)
			sub_len++;
	substr = (char *)malloc(sub_len + 1);
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + index, sub_len);
	substr[sub_len] = '\0';
	return (substr);
}

/*
int	main()
{
	char *s = NULL;
	int start = 2;
	char *new;
	int size = 6;
	new = ft_substr(s, start, size);
	printf ("%s", new);
	free(new);
	return 0;
}
*/
