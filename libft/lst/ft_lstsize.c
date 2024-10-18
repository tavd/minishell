/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:39:12 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/20 16:39:14 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	size_t	length;

	length = 0;
	current = lst;
	while (current != NULL)
	{
		length++;
		current = current->next;
	}
	return (length);
}

/*
int main()
{
	t_list	*head;

	head = NULL;
	ft_lstadd_front(&head, ft_lstnew("1"));
	ft_lstadd_front(&head, ft_lstnew("2"));
	ft_lstadd_front(&head, ft_lstnew("3"));

	printf("%i ", ft_lstsize(head));

}
*/
