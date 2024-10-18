/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:19:26 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/15 19:19:30 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	*ft_calloc(size_t num_elems, size_t elem_size)
{
	void			*array;

	if (elem_size != 0 && (num_elems * elem_size) / elem_size != num_elems)
		return (NULL);
	array = malloc(num_elems * elem_size);
	if (!array)
		return (NULL);
	ft_bzero(array, num_elems * elem_size);
	return (array);
}

/*
int main()
{
	
	ft_calloc(SIZE_MAX, 0);
}
*/

/*
int	main()
{
	size_t b = (size_t)INT_MAX;
	size_t a = 5;
	size_t c = SIZE_MAX;

	printf("errno = %i\n", errno);
	void *p = calloc(a, b);
	if (p == NULL)
		perror("er real");
	else
		free(p);

	void *ptr = ft_calloc(a, b);
	if (ptr == NULL)
		perror("er ft");
	else
		free(ptr);
	return 0;
}
*/
