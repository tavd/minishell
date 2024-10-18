/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:22:47 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/23 22:25:16 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	s1_len = ft_strlen(s1);
	const size_t	s2_len = ft_strlen(s2);
	const size_t	addition_of_lens = s1_len + s2_len + 1;
	char			*joined_str;

	if (addition_of_lens < s1_len
		|| addition_of_lens < s2_len
		|| !s1
		|| !s2)
		return (NULL);
	joined_str = (char *)malloc(addition_of_lens);
	if (!joined_str)
		return (NULL);
	ft_memcpy(joined_str, s1, s1_len);
	ft_memcpy(joined_str + s1_len, s2, s2_len);
	joined_str[addition_of_lens - 1] = '\0';
	return (joined_str);
}

/*
int main ()
{
	char *s1 = "dfg";
	char *s2 = "abc";


	char *new;
	new = ft_strjoin(s1, s2);
	printf(":%s:", new);
	free(new);
	return 0;
}	
*/
