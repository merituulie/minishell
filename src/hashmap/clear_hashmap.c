/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_hashmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:54:44 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:54:45 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
