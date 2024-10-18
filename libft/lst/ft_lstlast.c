/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:38:57 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/20 16:38:58 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current != NULL && current->next != NULL)
		current = current->next;
	return (current);
}

/*
int main()
{
	t_list	*head;

	head = NULL;
	ft_lstadd_front(&head, ft_lstnew("1"));
	ft_lstadd_front(&head, ft_lstnew("2"));
	ft_lstadd_front(&head, ft_lstnew("3"));

	t_list *last = ft_lstlast(head);
	printf("%s ", (char *)head->content);
	printf("%s ", (char *)last->content);
}
*/
