/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_specifiers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:55:17 by mzwart            #+#    #+#             */
/*   Updated: 2024/02/01 16:55:17 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// INT_MIN(11 chars) + 1 for null terminator
char	*decimal(va_list format_args)
{
	uint8_t	minus_padding;
	int64_t	input;
	char	*buffer;

	buffer = (char *)malloc(12);
	if (!buffer)
		return (NULL);
	input = va_arg(format_args, int32_t);
	minus_padding = 0;
	if (input < 0)
	{
		input = input * -1;
		buffer[0] = '-';
		minus_padding = 1;
	}
	uint_to_str((uint64_t)input, buffer + minus_padding, "0123456789");
	return (buffer);
}

//  UINT_MAX(10 chars) + 1 for null terminator
char	*unsigned_decimal(va_list format_args)
{
	char		*buffer;
	uint32_t	input;

	buffer = (char *)malloc(11);
	if (!buffer)
		return (NULL);
	input = va_arg(format_args, uint32_t);
	uint_to_str(input, buffer, "0123456789");
	return (buffer);
}

// uintmax in hex: ffffffff(8 chars) + 1 for null terminator
char	*hex(va_list format_args)
{
	char		*buffer;
	uint32_t	input;

	buffer = (char *)malloc(9);
	if (!buffer)
		return (NULL);
	input = va_arg(format_args, uint32_t);
	uint_to_str(input, buffer, "0123456789abcdef");
	return (buffer);
}

// uintmax in hex is FFFFFFFF(8 chars) + 1 for null terminator
char	*capital_hex(va_list format_args)
{
	char		*buffer;
	uint32_t	input;

	buffer = (char *)malloc(9);
	if (!buffer)
		return (NULL);
	input = va_arg(format_args, uint32_t);
	uint_to_str(input, buffer, "0123456789ABCDEF");
	return (buffer);
}

char	*void_ptr(va_list format_args)
{
	const char	*nil = "(nil)";
	void		*address;
	char		*str_address;

	str_address = (char *)malloc(24);
	if (!str_address)
		return (NULL);
	address = va_arg(format_args, void *);
	if (!address)
	{
		ft_memcpy(str_address, nil, 6);
		return (str_address);
	}
	str_address[0] = '0';
	str_address[1] = 'x';
	uint_to_str((uint64_t)address, str_address + 2, "0123456789abcdef");
	return (str_address);
}
