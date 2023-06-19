/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:23:05 by meskelin          #+#    #+#             */
/*   Updated: 2023/03/24 16:08:05 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hashmap.h"

/// @brief Get a value from the hashmap with the key.
/// @param head The first node on the hashmap.
/// @param key The key to search for a node.
/// @return The node with the key, NULL if not found.
t_node *get_value(t_node **head, char *key)
{
	t_node	*temp;

	temp = *head;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void	delete_head(t_node **head, char *key)
{
	t_node	*new_head;

	new_head = *head;
	if (ft_strcmp(new_head->key, key) == 0)
	{
		new_head = *head->next;
		free(*head);
		head = &new_head;
		return ;
	}
}

/// @brief Delete a value based on the key given as a paarameter.
/// @param head The first node of the hashmap.
/// @param key The key to search from the hashmap to be deleted.
void	delete_value(t_node **head, char *key)
{
	t_node	*temp;
	t_node	*to_be_deleted;

	if (!*head)
		return ;
	delete_head(head, key);
	temp = *head;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			to_be_deleted = temp;
			temp = temp->next;
			free(to_be_deleted);
			break ;
		}
		temp = temp->next;
	}
}

/// @brief Get the size of the hashmap.
/// @param head The first node on the hashmap.
/// @return int, count of the nodes in the hashmap.
int	hashmap_size(t_node **head)
{
	t_node	*temp;
	int		size;

	size = 0;
	temp = *head;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}
