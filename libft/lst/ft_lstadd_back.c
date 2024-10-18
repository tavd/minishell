/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:38:36 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/30 18:24:40 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!new)
		return ;
	last_node = ft_lstlast(*lst);
	if (last_node != NULL)
		last_node->next = new;
	else
		*lst = new;
}

/*
int main()
{
	t_list	*head;

	head = NULL;
	ft_lstadd_back(&head, ft_lstnew("1"));
	ft_lstadd_back(&head, ft_lstnew("2"));
	ft_lstadd_front(&head, ft_lstnew("3"));

	t_list *last = ft_lstlast(head);
	printf("last:%s ", (char *)last->content);
}
*/
