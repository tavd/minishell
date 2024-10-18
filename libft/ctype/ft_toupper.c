/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:26:31 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:26:39 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	ft_toupper(int c)
{
	return (c - 32 * (c >= 'a' && c <= 'z'));
}

/*
int main()
{
	printf("%c", ft_toupper('A'));
	printf("%c", ft_toupper('Z'));
	printf("%c", ft_toupper('9'));
	printf("%c", ft_toupper('a'));
	return 0;
}
*/
