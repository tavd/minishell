/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:55:06 by mzwart            #+#    #+#             */
/*   Updated: 2024/02/01 16:55:06 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

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
/*
int main()
{
	int long u = 123;

	unsigned int t = u;
	char	s[33];
	s[32] = '\0';
	ft_ltoa(u, s, "0123456789abcdef");
	printf("%s\len", s);
	printf("%x", u);
}
*/
