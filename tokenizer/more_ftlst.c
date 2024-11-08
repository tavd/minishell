#include "libft/libft.h"

t_list	*ft_node_at_count(t_list *lst, int count)
{
	if (!lst || count < 0)
		return(NULL);
	while (lst->next != NULL && count > 1)
	{
		lst = lst->next;
		--count;
	}
	return (lst);
}

t_list	*ft_lstfind(t_list *lst, bool (*compare_fn)(void *content))
{
	if (compare_fn == NULL)
		return (NULL);
	while (lst)
	{
		if (compare_fn(lst->content))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

// CLEANLY remove node form list
void	ft_lst_remove_node(t_list **node_to_remove, void (*del_content_fn)(void *content))
{
	t_list	*next_node;

	if (!node_to_remove || !*node_to_remove)
		return ;
	next_node = (*node_to_remove)->next;
	ft_lstdelone(*node_to_remove, del_content_fn);
	*node_to_remove = next_node;
}

// iterates over linked list and applies a fn to every linked list node.
// the fn gets passed an indirect pointer of a node to allow for easy modification
// of the linked list itself. (it makes it so you dont need a ptr to previous node ).
int	ft_lstiter_mod(t_list **lst, int (*mod_fn)(t_list **))
{
	t_list	**lst_item;
	int	fn_return;

	if (!lst || !mod_fn)
		return 0;
	fn_return = 0;
	lst_item = lst;
	while (*lst_item)
	{
		fn_return = mod_fn(lst_item);
		if (*lst_item)
			lst_item = &(*lst_item)->next;
	}
	return (fn_return);
}
