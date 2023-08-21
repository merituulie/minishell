
#include "../../headers/hashmap.h"

static void	ft_clr_rec(t_node *node)
{
	if (!node)
		return ;
	ft_clr_rec(node->next);
	node->next = NULL;
	free(node->key);
	node->key = NULL;
	free(node->value);
	node->value = NULL;
	free(node);
}

/// @brief Clear out the whole hashmap.
/// @param head The first node to the hashmap.
void	clear_hashmap(t_node **head)
{
	if (!head || !*head)
		return ;
	ft_clr_rec(*head);
	*head = NULL;
}
