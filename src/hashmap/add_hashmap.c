/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hashmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:54:40 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:54:41 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/hashmap.h"

t_node	*new_node(char *key, char *value)
{
	t_node	*new;

	new = (t_node *)ft_calloc(1, sizeof(*new));
	if (!new)
		malloc_error();
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_node	*get_last(t_node **head)
{
	t_node	*temp;

	if (!head || !*head)
		return (NULL);
	temp = *head;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

/// @brief Add a new value to the end of the hashmap.
/// @param head The first node of the hashmap.
/// @param key The key for searching the value from the hashmap.
/// @param value The data that the node is holding.
t_node	**set_value(t_node **head, char *key, char *value)
{
	t_node	*temp;

	if (!head || !*head)
	{
		head = (t_node **)ft_calloc(1, sizeof(*head));
		if (!head)
			malloc_error();
		*head = new_node(key, value);
	}
	else
	{
		temp = get_last(head);
		temp->next = new_node(key, value);
	}
	return (head);
}
