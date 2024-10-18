/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:25:06 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:26:27 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	ft_tolower(int c)
{
	return (c + 32 * (c >= 'A' && c <= 'Z'));
}

// int main()
// {

// 	printf("%c", ft_tolower('A'));
// 	printf("%c", ft_tolower('Z'));
// 	printf("%c", ft_tolower('9'));
// 	printf("%c", ft_tolower('a'));
// 	return 0;
// }
