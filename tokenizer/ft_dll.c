#include "lst_embed.h"

void	ft_lst_embed_addfront(t_lst_embed *new, t_lst_embed *head)
{

}

void	ft_lst_embed_add(t_lst_embed *new, t_lst_embed *prev, t_lst_embed *next)
{
	head->next = new;
	head->prev = new;
}

t_lst_embed	*ft_lst_embed_get_tail(t_lst_embed *head)
{
	
}

void	ft_lst_embed_addback(t_lst_embed **head, t_lst_embed *new_node)
{
	t_lst_embed	*tail_node;

	if (!new_node)
		return ;
	tail_node = ft_dll_get_tail(*head);
	tail_node->next = new_node;
	new_node->prev = tail_node;
	new_node->next = NULL;
}

/** 
 * list_for_each_entry  -       iterate over list of given type 
 * @pos:        the type * to use as a loop counter. 
 * @head:       the head for your list. 
 * @member:     the name of the list_struct within the struct. 
 */

void	ft_lst_for_each_entry(



int main()
{
	t_lst_embed	lst;
	t_lst_token	tok;
	
	tok = (t_lst_token)lst;

	lst = (t_lst_embed)tok;
}
