/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:22:39 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/30 15:26:38 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/*
void	add_index(unsigned int index, char *c)
{
	*c = *c + index;
}
*/

void	ft_striteri(char *str, void (*function)(unsigned int i, char *c))
{
	size_t			str_len;
	unsigned int	i;

	if (!str || !function)
		return ;
	str_len = ft_strlen(str);
	i = 0;
	while (i < str_len)
	{
		function(i, (str + i));
		++i;
	}
}

/*
int main ()
{
	char *s = NULL;

	ft_striteri(s, add_index);
	printf("%s", s);

	return 0;
	}
*/

/*
int main ()
{
	char *s = "aaaaaaa";
	char *y = ft_strmapi(s, add_index);

	printf("%s", y);

	return 0;
}
*/
