/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:21:50 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/30 18:17:12 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <fcntl.h>

static void	*reverse_str(char *str, int str_len)
{
	int		i;
	char	tmp;

	i = 0;
	str[str_len] = '\0';
	str_len--;
	while (i <= str_len)
	{
		tmp = str[i];
		str[i] = str[str_len];
		str[str_len] = tmp;
		++i;
		str_len--;
	}
	return (str);
}

static void	nbr_to_str(int unmodified_number, char *str)
{
	int			str_len;
	long int	number;

	number = unmodified_number;
	str_len = 0;
	if (number < 0)
		number *= -1;
	while (number >= 10)
	{
		str[str_len++] = (number % 10) + '0';
		number /= 10;
	}
	str[str_len++] = number + '0';
	if (unmodified_number < 0)
		str[str_len++] = '-';
	str = reverse_str(str, str_len);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	number[12];
	int		str_len;

	nbr_to_str(n, number);
	str_len = ft_strlen(number);
	if (n < 0)
		str_len++;
	write(fd, number, ft_strlen(number));
}

// int main()
// {
// 	ft_putnbr_fd(INT_MAX, 1);
// 	return 0;
// }
