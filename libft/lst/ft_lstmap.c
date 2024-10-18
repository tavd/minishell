/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:39:00 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/20 16:39:01 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
/*
void	*foo(void *c)
{
	printf("foo:%s->", (char *)c);
	return (c);
}

void	del(void *c)
{
	printf("\ndelete:%s", (char *)c);
}
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstcpy;
	t_list	*newnode;
	void	*newcontent;

	if (!lst || !f || !del)
		return (NULL);
	lstcpy = NULL;
	while (lst != NULL)
	{
		newcontent = f(lst->content);
		newnode = ft_lstnew(newcontent);
		if (!newnode)
		{
			del(newcontent);
			ft_lstclear(&lstcpy, del);
			return (NULL);
		}
		ft_lstadd_back(&lstcpy, newnode);
		lst = lst->next;
	}
	return (lstcpy);
}

/*
int main ()
{
	t_list *	head = NULL;
	ft_lstadd_back(&head, ft_lstnew("1"));
	ft_lstadd_back(&head, ft_lstnew("2"));
	ft_lstadd_back(&head, ft_lstnew("3"));
	printf("\n");
	t_list	*cpy;
	cpy = ft_lstmap(head, foo, del);
	t_list	*cpyhead = cpy;

	printf("\n");
	while (cpy != NULL)
	{
		printf("%s->", (char *)cpy->content);
		cpy = cpy->next;
	}
	ft_lstclear(&head, del);
	ft_lstclear(&cpyhead, del);

}
*/
