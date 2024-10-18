/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:38:46 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/23 21:58:55 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/*
void	wl(void *content)
{
	printf("del:%s ", (char *)content);
}
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*traverse_lst_ptr;
	t_list	*tmp_for_free;

	traverse_lst_ptr = *lst;
	while (traverse_lst_ptr != NULL && del != NULL)
	{
		del((traverse_lst_ptr)->content);
		tmp_for_free = traverse_lst_ptr;
		traverse_lst_ptr = (traverse_lst_ptr)->next;
		free(tmp_for_free);
	}
	*lst = NULL;
}

/*
int	main()
{
	t_list *head;

	head = NULL;

	ft_lstadd_back(&head, ft_lstnew("1"));
	ft_lstadd_back(&head, ft_lstnew("2"));
	ft_lstadd_back(&head, ft_lstnew("3"));
	ft_lstadd_back(&head, ft_lstnew("4"));

	ft_lstclear(&head->next, wl);
	while (head != NULL)
	{
		printf("%s->", (char *)head->content);
		head = head->next;
	}
}
*/
