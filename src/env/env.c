/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:25:06 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/03 17:10:09 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"
#include "../../headers/env.h"

static void	print_env(t_node **head)
{
	t_node	*temp;

	temp = *head;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

static int	count_length(t_node **nodes)
{
	int		length;
	t_node	*temp;

	length = 0;
	temp = *nodes;
	while (temp)
	{
		length += ft_strlen(temp->key) + ft_strlen(temp->value) + 2;
	}
	length += 1;
	return (length);
}

static void	copy_keyvalue(char **output, t_node *node, int *i)
{
	int	key_len;
	int	value_len;

	key_len = ft_strlen(node->key);
	ft_strlcpy(&(*output)[*i], node->key, key_len);
	ft_strlcpy(&(*output)[*i + key_len], "=", 1);
	value_len = ft_strlen(node->value);
	ft_strlcpy(&(*output)[*i + key_len + 1], node->value, value_len);
	ft_strlcpy(&(*output)[*i + key_len + value_len + 1], "\n", 1);
	i += key_len + value_len + 2;
}

static char	*to_string(t_env **env)
{
	int		i;
	int		length;
	char	*output;
	t_node	*temp_node;

	length = count_length((*env)->vars);
	output = (char *)ft_calloc(length, sizeof(*output));
	temp_node = *(*env)->vars;
	i = 0;
	while (temp_node)
	{
		copy_keyvalue(&output, temp_node, &i);
		temp_node = temp_node->next;
	}
	return (output);
}

char	*ft_env(t_env **env, int isPiped)
{
	if (isPiped)
		return (to_string(env));
	else
	{
		print_env((*env)->vars);
		return (NULL);
	}
}
