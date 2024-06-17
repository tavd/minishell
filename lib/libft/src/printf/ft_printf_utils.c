/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:06:58 by irsander          #+#    #+#             */
/*   Updated: 2024/06/17 15:53:08 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	printf_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
		i++;
	i = write(1, s, i);
	return (i);
}

int	printf_putptr(void *p)
{
	int				length;
	unsigned long	num;

	length = 0;
	num = (unsigned long)p;
	if (p == NULL)
	{
		length += printf_putstr("0x0");
		return (length);
	}
	if (num >= 16)
		length += printf_putptr((void *)(num / 16));
	if (length == 0)
		length += printf_putstr("0x");
	num = num % 16;
	if (num < 10)
		length += ft_putchar(num + '0');
	else
		length += ft_putchar(num + ('a' - 10));
	return (length);
}

int	printf_putnbr(long num, int base, int u_nbr, int upcase)
{
	int	length;

	length = 0;
	if (u_nbr == 1)
		num = (unsigned int)num;
	if (num < 0 && base <= 10)
	{
		length += ft_putchar('-');
		num = -num;
	}
	if (num >= base)
		length += printf_putnbr(num / base, base, u_nbr, upcase);
	num = num % base;
	if (num < 10)
		length += ft_putchar(num + '0');
	else
	{
		if (upcase == 1)
			length += ft_putchar(num + ('a' - 10));
		else if (upcase == 2)
			length += ft_putchar(num + ('A' - 10));
	}
	return (length);
}
