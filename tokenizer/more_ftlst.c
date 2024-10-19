#include "libft/libft.h"

t_list	*ft_node_at_count(t_list *lst, int	count)
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

