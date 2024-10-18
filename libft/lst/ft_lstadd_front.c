/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:38:42 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/20 16:38:43 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
int main(void)
{
	t_list *head;
	t_list *new;
	head = NULL;

	new = ft_lstnew("str");
	ft_lstadd_front(&head, new);
	ft_lstadd_front(&head, ft_lstnew("andere str"));
	printf("%s\n", (char *)head->content);
}
*/
