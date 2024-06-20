/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:24:32 by irissanders       #+#    #+#             */
/*   Updated: 2024/06/17 15:45:40 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;

	nbr = n;
	while (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr > 9)
		ft_putnbr_fd (nbr / 10, fd);
	nbr = nbr % 10;
	if (nbr >= 0 && nbr <= 9)
		ft_putchar_fd(nbr + '0', fd);
}
