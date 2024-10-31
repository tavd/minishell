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

#include "libft/string.h"
#include "libft/stdlib.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*joined_str;
	size_t			s1_len;
	size_t			s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined_str = (char *)ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!joined_str)
		return (NULL);
	ft_strlcpy(joined_str, s1, s1_len + 1);
	ft_strlcat(joined_str, s2, s1_len + s2_len + 1);
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
