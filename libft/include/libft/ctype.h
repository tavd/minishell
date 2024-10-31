/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:06:51 by mzwart            #+#    #+#             */
/*   Updated: 2024/08/08 16:09:32 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTYPE_H
# define CTYPE_H

# include <stdbool.h>
# include <limits.h>
# include <stdint.h>

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

int		ft_tolower(int c);
int		ft_toupper(int c);

// NOTE: make this  into new module?
bool	ft_is_int(char *str);
bool	ft_is_int32(char *str);
int		ft_isdecimal(const char *str);

#endif
