/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:38:50 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/20 16:38:51 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/*
void	del(void *content)
{
	printf("del:%s\n", (char *)content);
}
*/

void	ft_lstdelone(t_list *lst, void (*del)(void *content))
{
	if (lst != NULL && del != NULL)
	{
		del(lst->content);
		free(lst);
	}
}

/*
int	main()
{
	t_list *head = NULL;

	ft_lstadd_front(&head, ft_lstnew("1"));
	ft_lstadd_front(&head, ft_lstnew("2"));
	ft_lstadd_front(&head, ft_lstnew("3"));
	ft_lstadd_front(&head, ft_lstnew("4"));

	t_list *tmp = head->next;
	head->next = head->next->next;
	ft_lstdelone(tmp,del);
	while (head != NULL)
	{
		printf("%s->", (char *)head->content);
		head = head->next;
	}
}
*/
