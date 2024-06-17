/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:51:57 by irsander          #+#    #+#             */
/*   Updated: 2023/10/10 16:47:00 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

// int main(void)
// {
//     size_t i;
//     size_t j;
//     char str [] = "hellogoodbye";
//     char str2 [] = "hellogoodbye";

//     printf("original string: %s\n", str);
//     ft_bzero(str, 5);
//     bzero(str2, 5);

//     i = 0;
//     j = 0;
//     while (i < sizeof(str))
//         printf("modified string, my function: %c\n",str[i++]);
//     while (j < sizeof(str2))
//         printf("modified string, og function: %c\n",str2[j++]);
// }