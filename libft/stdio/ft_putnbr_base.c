/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mzwart <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/06 16:09:25 by mzwart        #+#    #+#                 */
/*   Updated: 2023/09/06 17:10:20 by mzwart        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

int	ft_check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (-1);
		j = 0;
		while (base[j])
		{
			if (base[i] == base[j] && i != j)
				return (-1);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (-1);
	return (i);
}

void	ft_putnbr_base(int nb, char *base)
{
	const int	base_length = ft_check_base(base);
	long int	nbr;
	char		converted_nbr[30];
	int			i;

	if (base_length == -1)
		return ;
	i = 0;
	nbr = nb;
	if (nbr < 0)
		nbr *= -1;
	while ((nbr / base_length) > 0)
	{
		converted_nbr[i] = base[nbr % base_length];
		nbr /= base_length;
		i++;
	}
	converted_nbr[i] = base[nbr % base_length];
	if (nb < 0)
		write(1, "-", 1);
	while (i-- >= 0)
		write(1, &converted_nbr[i + 1], 1);
}
/*
int	main()
{
	int nbr;

	nbr = INT_MAX;
	ft_putnbr_base(nbr,"0123456789");
	write(1, "\n", 1);
	ft_putnbr_base(nbr,"01");
	write(1, "\n", 1);
	ft_putnbr_base(nbr,"0123456789ABCDEF");
	write(1, "\n", 1);
	ft_putnbr_base(nbr,"poneyvif");
	write(1, "\n", 1);

	nbr = INT_MIN;
	ft_putnbr_base(nbr,"0123456789");
	write(1, "\n", 1);
	ft_putnbr_base(nbr,"01");
	write(1, "\n", 1);
	ft_putnbr_base(nbr,"0123456789ABCDEF");
	write(1, "\n", 1);
	ft_putnbr_base(nbr,"poneyvif");
	return (0);	
}
*/
