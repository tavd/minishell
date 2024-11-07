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

static int	count_digits(int n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n /= 10;
		++count;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		num_len;
	char	*buf;
	bool	is_negative;

	is_negative = false;
	if (n < 0)
		is_negative = true;
	num_len = count_digits(n);
	buf = malloc(num_len + is_negative + 1);
	if (!buf)
		return (NULL);
	buf[num_len + is_negative] = '\0';
	while (n != 0)
	{
		buf[num_len + is_negative - 1] = (n % 10) * (1 - is_negative * 2) + '0';
		n /= 10;
		--num_len;
	}
	if (is_negative)
		buf[0] = '-';
	return (buf);
}

// #include <stdio.h>
// #include <stdint.h>
// int main()
// {
// 	int	n = -321;
//
// 	char *str = ft_itoa(n);
//
// 	n = (uint16_t)n;
// 	printf("%u", n);
//
//
// 		return 0;
// }

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
