/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:07:02 by irsander          #+#    #+#             */
/*   Updated: 2024/01/14 13:05:49 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	string_conversion(va_list args, char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int), 10, 0, 0));
	else if (c == 'u')
		return (ft_putnbr(va_arg(args, int), 10, 1, 0));
	else if (c == 'x')
		return (ft_putnbr(va_arg(args, int), 16, 1, 1));
	else if (c == 'X')
		return (ft_putnbr(va_arg(args, int), 16, 1, 2));
	else if (c == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		length;

	i = 0;
	length = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			i++;
			length += string_conversion(args, s[i]);
		}
		else
			length += ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (length);
}

// int main(void)
// {
// 	ft_printf("- c: print single character test\n");
// 	char character = 'a';
// 	ft_printf("  my printf: %c\n", character);
// 	printf("  og printf: %c\n\n", character);

// 	ft_printf("- s: print string test\n");
// 	char *string = "lol";
// 	ft_printf("  my printf: %s\n", string);
// 	printf("  og printf: %s\n\n", string);

// 	ft_printf("- %: double percentage sign test\n");
// 	ft_printf("  my printf: %%\n");
// 	printf("  og printf: %%\n\n");

// 	ft_printf("- i: print integer in base 10 test\n");
// 	int	num = 543;
// 	ft_printf("  my printf: %i\n", num);
// 	printf("  og printf: %i\n\n", num);

// 	ft_printf("- d: print decimal in base 10 test\n");
// 	int	decml = 42;
// 	ft_printf("  my printf: %d\n", decml);
// 	printf("  og printf: %d\n\n", decml);

// 	ft_printf("- u: print unsigned int in base 10 test\n");
// 	int	unsint = -123;
// 	ft_printf("  my printf: %u\n", unsint);
// 	printf("  og printf: %u\n\n", unsint);

// 	ft_printf("- x: print hexadecimal in base 16 lowercase test\n");
// 	int	hex_lowcase = 0x24ab6f;
// 	ft_printf("  my printf: %x\n", hex_lowcase);
// 	printf("  og printf: %x\n\n", hex_lowcase);

// 	ft_printf("- x: print hexadecimal in base 16 uppercase test\n");
// 	int	hex_upcase = 0x24ab6f;
// 	ft_printf("  my printf: %X\n", hex_upcase);
// 	printf("  og printf: %X\n\n", hex_upcase);

// 	ft_printf("- p: print pointer test\n");
// 	char *pointer = "h";
// 	ft_printf("  my printf: %p\n", pointer);
// 	printf("  og printf: %p\n\n", pointer);
// 	return (0);
// }