/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:43:11 by mzwart            #+#    #+#             */
/*   Updated: 2024/07/31 19:43:50 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static char	*reverse_strndup(char *str, int str_len)
{
	char	*str_cpy;

	str_cpy = (char *)malloc((size_t)str_len + 1);
	if (!str_cpy)
		return (NULL);
	str_cpy[str_len] = '\0';
	while (--str_len > -1)
	{
		str_cpy[str_len] = *str;
		str++;
	}
	return (str_cpy);
}

char	*ft_itoa(int unmodified_number)
{
	char		*int_str;
	int			str_len;
	char		tmp_str[12];
	long int	number;

	number = unmodified_number;
	str_len = 0;
	if (number < 0)
		number *= -1;
	while (number >= 10)
	{
		tmp_str[str_len++] = (number % 10) + '0';
		number /= 10;
	}
	tmp_str[str_len++] = number + '0';
	if (unmodified_number < 0)
		tmp_str[str_len++] = '-';
	int_str = reverse_strndup(tmp_str, str_len);
	return (int_str);
}

/*
int main ()
{
	char *s;
	s = ft_itoa(2);
	printf("%s", s);
	free(s);


	return 0;
}
*/
