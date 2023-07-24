/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:25:06 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/21 10:48:56 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	copy_keyvalue(char **output, t_node *node)
{
	char	*temp;

	if (!output || !*output)
		temp = ft_strjoin(node->key, "");
	else
		temp = ft_strjoin(*output, node->key);
	temp = ft_strjoin(temp, "=");
	temp = ft_strjoin(temp, node->value);
	temp = ft_strjoin(temp, "\n");
	free(*output);
	*output = temp;
}

char	*env_to_string(t_env **env)
{
	char	*output;
	t_node	*temp_node;

	temp_node = *(*env)->vars;
	output = NULL;
	while (temp_node)
	{
		copy_keyvalue(&output, temp_node);
		temp_node = temp_node->next;
	}
	return (output);
}

void	ft_env(t_env **env)
{
	ft_putstr_fd(env_to_string(env), 1);
}
