/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_lst.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:13:23 by mzwart            #+#    #+#             */
/*   Updated: 2024/10/31 13:13:23 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERIC_LST_H
# define GENERIC_LST_H

# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;


t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new_node);
void		ft_lstadd_back(t_list **lst, t_list *new_node);
int			ft_lstsize(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*f)(void *content));
void		ft_lstiter(t_list *lst, void (*f)(void *content));
t_list		*ft_lstmap(t_list *l, void *(*f)(void *ct), void(*d)(void *ct));

#endif
