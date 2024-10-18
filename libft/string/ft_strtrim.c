/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:24:57 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:24:57 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	start_trim;
	size_t	end_trim;
	char	*trimmed_str;

	if (!str || !set)
		return (NULL);
	end_trim = ft_strlen(str);
	while (str[end_trim - 1] && ft_strchr(set, str[end_trim - 1]))
		end_trim--;
	start_trim = 0;
	while (str[start_trim] && ft_strchr(set, str[start_trim]))
	{
		start_trim++;
		end_trim--;
	}
	trimmed_str = ft_substr(str, start_trim, end_trim);
	if (!trimmed_str)
		return (NULL);
	return (trimmed_str);
}
/*
int main()
{
	char *s = "abcddfefccbabc";
	char *set = "abc";

	char *new;
	new = ft_strtrim(s, set);
	printf("%s", new);
	if (new)
		free(new);
	
	return 0;
	}
*/
