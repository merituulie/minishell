/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hashmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:23:05 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/08 11:55:15 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

/// @brief Get a value from the hashmap with the key.
/// @param head The first node on the hashmap.
/// @param key The key to search for a node.
/// @return The node with the key, NULL if not found.
t_node	*get_value(t_node **head, char *key)
{
	t_node	*temp;

	temp = *head;
	while (temp)
	{
		if (ft_strncmp_all(temp->key, key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/// @brief Checks a value from the hashmap with the value.
/// @param head The first node on the hashmap.
/// @param value The value to search for a node.
/// @return The node with the key, NULL if not found.
t_node	*check_value(t_node **head, char *value)
{
	t_node	*temp;

	temp = *head;
	while (temp)
	{
		if (ft_strncmp_all(temp->value, value) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static int	delete_head(t_node **head, char *key)
{
	t_node	*new_head;

	new_head = NULL;
	if (ft_strncmp_all((*head)->key, key) == 0)
	{
		if ((*head)->next)
		{
			new_head = (*head)->next;
			*head = new_head;
			free(new_head);
		}
		else
			free(*head);
		return (1);
	}
	return (0);
}

/// @brief Delete a value based on the key given as a paarameter.
/// @param head The first node of the hashmap.
/// @param key The key to search from the hashmap to be deleted.
void	delete_value(t_node **head, char *key)
{
	t_node	*previous;
	t_node	*current;

	if (!*head)
		return ;
	if (delete_head(head, key))
		return ;
	previous = *head;
	current = (*head)->next;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			free(current->key);
			free(current->value);
			previous->next = current->next;
			free(current);
			break ;
		}
		previous = current;
		current = current->next;
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
