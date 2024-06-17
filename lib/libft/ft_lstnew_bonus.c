/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:44:56 by irissanders       #+#    #+#             */
/*   Updated: 2023/11/07 15:28:37 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

// int main(void)
// {
// 	int	value;
// 	t_list *list;

// 	value = 5;
// 	list = ft_lstnew(&value);
// 	if (list)
// 	{
// 		printf("%i\n", *(int *)(list->content));
// 		free(list);
// 	}
// 	else
// 		printf("ERROR");
// 	return (0);
// }
