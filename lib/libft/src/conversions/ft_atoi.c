/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:48:17 by irsander          #+#    #+#             */
/*   Updated: 2023/10/11 19:56:42 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	neg_num;
	int	num;

	i = 0;
	neg_num = 1;
	num = 0;
	while ((s[i] >= 9 && s[i] <= 13)
		|| (s[i] == 32))
		i++;
	if ((s[i] == '-' || s[i] == '+')
		&& (s[i +1] >= '0' && s[i +1] <= '9'))
	{
		if (s[i] == '-')
			neg_num = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		num = num * 10 + (s[i] - '0');
		i++;
	}
	return (num * neg_num);
}

// int main(void)
// {
//     char *s;

//     s = "123";

//     printf("%i\n", ft_atoi(s));
// }