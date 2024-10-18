/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_specifiers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:54:22 by mzwart            #+#    #+#             */
/*   Updated: 2024/02/01 16:54:22 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "libft/libft.h"

char	*string(va_list format_args)
{
	char		*str;

	str = va_arg(format_args, char *);
	if (!str)
		return ("(null)");
	return (str);
}

char	*chars(va_list format_args)
{
	char	*char_str;

	char_str = (char *)malloc(2);
	if (!char_str)
		return (NULL);
	char_str[0] = (unsigned char)va_arg(format_args, int);
	char_str[1] = '\0';
	return (char_str);
}

char	*echo_percent(va_list nothing)
{
	(void)nothing;
	return ("%");
}

static	void	reverse_str(char **buffer, uint8_t len)
{
	char		tmp;
	uint8_t		s;

	s = 0;
	while (--len > s)
	{
		tmp = (*buffer)[len];
		(*buffer)[len] = (*buffer)[s];
		(*buffer)[s] = tmp;
		s++;
	}
}

// add bool to do sign or unsign: need 128 Bit Int for this :(
char	*uint_to_str(uint64_t value, char *buffer, char *base)
{
	const uint8_t	radix = ft_strlen(base);
	uint64_t		number;
	uint8_t			len;

	if (!buffer)
		return (NULL);
	len = 0;
	number = value;
	while (number >= radix)
	{
		buffer[len++] = base[(number % radix)];
		number /= radix;
	}
	buffer[len++] = base[(number % radix)];
	reverse_str(&buffer, len);
	buffer[len] = '\0';
	return (buffer);
}
