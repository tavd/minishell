/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:28:12 by irissanders       #+#    #+#             */
/*   Updated: 2023/11/07 15:23:26 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int main(void)
// {
// 	t_list *first_node;
// 	t_list *second_node;
// 	int	first_value = 5;
// 	int	second_value = 7;

// 	first_node = ft_lstnew(&first_value);
// 	second_node = ft_lstnew(&second_value);
// 	ft_lstadd_front(&first_node, second_node);
// 	printf("first node: %i\n", *(int *)(first_node->content));
// 	printf("second node: %i\n", *(int *)(first_node->next->content));
// }
