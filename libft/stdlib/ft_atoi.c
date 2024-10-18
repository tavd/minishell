/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:18:21 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/30 17:00:59 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	ft_atoi(const char *nptr)
{
	int	number;
	int	neg;

	neg = 1;
	number = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		number = number * 10 + (*nptr - '0');
		nptr++;
	}
	return (number * neg);
}

/*
int main()
{
	char *s = "\t\f\n\r\v   469";
	char *m = "-21474836481";
	char *t = "-2212";
	int i =	atoi(s);


	int x = ft_atoi(s);

	printf("%d", i);
	printf("\nmy function:\n");
	printf("%d\n", x);
	//printf("\n%d", __INT_MIN__);

	return 0;
}
*/
