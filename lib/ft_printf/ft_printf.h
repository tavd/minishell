/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:07:06 by irsander          #+#    #+#             */
/*   Updated: 2024/05/23 12:21:35 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

//ft_printf.c
int		ft_printf(const char *s, ...);
int		string_conversion(va_list args, char c);

//ft_printf_utils.c
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr(long num, int base, int u_nbr, int upcase);
int		ft_putptr(void *p);

#endif