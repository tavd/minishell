/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:33:14 by mzwart            #+#    #+#             */
/*   Updated: 2024/08/08 16:10:07 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include "libft/ctype.h"
# include "libft/string.h"
# include "libft/stdlib.h"

// BONUS
# include "libft/generic_lst.h"
// # include "libft/embedded_lst.h"

// #inlcude "libft/stdio.h"
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *str, int fd);
void		ft_putendl_fd(char *str, int fd);
void		ft_putnbr_fd(int n, int fd);
//void		printf :make a better printf implementation...

#endif
