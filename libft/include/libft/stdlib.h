/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdlib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:34:17 by mzwart            #+#    #+#             */
/*   Updated: 2024/10/31 10:34:17 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDLIB_H
# define STDLIB_H

# include <stdlib.h>

double		ft_atof(const char *str);
void		*ft_calloc(size_t num_elems, size_t elem_size);
char		**ft_split(const char *str, char delimiter);
char		*ft_itoa(int number);
int			ft_abs(int j);
int			ft_atoi(const char *str);

#endif
