/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:07:03 by irissanders       #+#    #+#             */
/*   Updated: 2023/11/07 15:39:59 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// int main(int argc, char *argv[])
// {
// 	t_list *head = NULL;
// 	t_list *new_node;
// 	int i;
// 	int number;
// 	int result;

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
// 	result = ft_lstsize(head);
// 	printf("amount of nodes: %i\n", result);
// }