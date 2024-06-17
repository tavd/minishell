/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: irsander <irsander@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 10:07:48 by irissanders   #+#    #+#                 */
/*   Updated: 2023/10/15 12:24:23 by irissanders   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_counter(int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		counter++;
	else if (n < 0)
	{
		counter++;
		n = n * -1;
	}
	while (n > 0)
	{
		counter++;
		n = n / 10;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = char_counter(n);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		n = n * -1;
	}
	if (n == 0)
		s[0] = '0';
	s[len] = '\0';
	while (n > 0)
	{
		len --;
		s[len] = n % 10 + '0';
		n = n / 10;
	}
	return (s);
}

// int main(void)
// {
//   int n = 1234;

// printf("%s", ft_itoa(n));
// }