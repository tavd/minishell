/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:20:24 by mzwart            #+#    #+#             */
/*   Updated: 2024/02/27 16:12:47 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

# include "libft/string.h"
# include "libft/stdlib.h"

# define VEC_SIZE 42

typedef struct s_vector
{
	char		*content;
	size_t		size;
	size_t		used;
}		t_vector;

typedef char	*(*t_va_function)(va_list);

// COMPILER ATTRIBUTE FOR INCORRECT FORMATTING WARNINGS
int			ft_printf(const char *format, ...)
			__attribute__ ((format (printf, 1, 2)));

int			ft_printf(const char *format, ...);

char		*echo_percent(va_list nothing);
char		*decimal(va_list format_args);
char		*unsigned_decimal(va_list format_args);
char		*string(va_list format_args);
char		*chars(va_list format_args);
char		*hex(va_list format_args);
char		*capital_hex(va_list format_args);
char		*void_ptr(va_list format_args);

//helper
char		*uint_to_str(uint64_t value, char *buffer, char *base);

#endif
