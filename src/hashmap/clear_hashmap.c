/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_hashmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:53:34 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/03 18:21:27 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/hashmap.h"

static void	ft_clr_rec(t_node *node)
{
	if (!node)
		return ;
	ft_clr_rec(node->next);
	node->next = NULL;
	node->key = NULL;
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
