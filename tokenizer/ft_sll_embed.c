
// Free's the node and switches its address out for address of the next node
// Returns if no current node.
void	ft_sll_remove_node(t_lst_embed **node_to_remove,
	void (*free_content_fn)(void *content_after_lst_embed))
{
	t_lst_embed	*next_node;
	
	if (node_to_remove == NULL || *node_to_remove == NULL)
		return ;
	next_node = (*node_to_remove)->next;
	if (free_content_fn)
		free_content_fn((void *)*node_to_remove);
	free(*node_to_remove);
	*node_to_remove = next_node;
}
	//content = (void *)*node_to_remove; // + sizeof(t_lst_embed);

void	ft_sll_addback(t_lst_embed **head, t_lst_embed *new_node)
{
	t_lst_embed	*current;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	new_node->next = NULL;
	new_node->prev = NULL;
}
