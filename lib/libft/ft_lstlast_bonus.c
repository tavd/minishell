/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:52:06 by irissanders       #+#    #+#             */
/*   Updated: 2023/11/07 15:27:14 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// int main(int argc, char *argv[])
// {
// 	t_list *head = NULL;
// 	t_list *new_node;
// 	int i;
// 	int number;
// 	t_list *result;

// 	i = 1;
// 	while (argc > i)
// 	{
// 		number = ft_atoi(argv[i]);
// 		new_node = ft_lstnew(&number);
// 		if (new_node)
// 			ft_lstadd_front(&head, new_node);
// 		else
// 		{
// 			printf("ERROR: failed creating new node\n");
// 			break;
// 		}
// 		i++;
// 	}
// 	result = ft_lstlast(head);
// 	printf("value of last node: %i\n", *(int *)result->content);
// }
