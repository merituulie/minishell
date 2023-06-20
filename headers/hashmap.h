/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:14:05 by meskelin          #+#    #+#             */
/*   Updated: 2023/06/20 13:27:39 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include <stdlib.h>

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
}	t_node;

t_node	*new_node(char *key, char *value);
int		hashmap_size(t_node **head);
t_node	*get_value(t_node **head, char *key);
void	set_value(t_node **head, char *key, char *value);
void	delete_value(t_node **head, char *key);
void	clear_hashmap(t_node **head);

#endif
