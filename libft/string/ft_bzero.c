/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:22:59 by mzwart            #+#    #+#             */
/*   Updated: 2023/10/31 20:26:44 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	*ft_bzero(void *block, size_t n)
{
	ft_memset(block, 0, n);
	return (block);
}

/*
int main()
{
    int size = 5;
    char c  = ' ';
    int *ptr = malloc(size);
    bzero(ptr, size);

    int *p = malloc(size);
    ft_bzero(p, size);

    int i = 0;
    while (i++ < size)
    {
        printf("%c", *ptr);
    }
    i = 0;
    printf("\n");
    while (i++ < size)
    {
        printf("%c", *p);
    }
    return 0;
}
*/
