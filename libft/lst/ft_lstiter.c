/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:38:53 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/20 16:38:54 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/*
void	foo(void *c)
{
	printf("%s->", (char *)c);
}
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL && f != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
int main ()
{
	t_list *	head = NULL;

	ft_lstadd_front(&head, ft_lstnew("1"));
	ft_lstadd_front(&head, ft_lstnew("2"));
	ft_lstadd_front(&head, ft_lstnew("3"));

	ft_lstiter(head, foo);
}
*/
