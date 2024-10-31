/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:28:53 by mzwart            #+#    #+#             */
/*   Updated: 2024/10/31 14:28:53 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs(int j)
{
	if (j >= 0)
		return (j);
	else
		return (-j);
}

// #include <stdlib.h>
// #include <stdio.h>
// #include <limits.h>
//
// int main()
// {
// 	// NOTE: REAL FUNCTION also return's the overflown number

// 	printf("%i", abs(INT_MIN));
// }
