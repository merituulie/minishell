/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:08:29 by rmakinen          #+#    #+#             */
/*   Updated: 2023/07/20 12:08:38 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../headers/env.h"
#include "../../libft/libft.h"

int	ft_pwd(t_env **env)
{
	t_node	*correct_node;
	int		i;

	i = 0;
	if (!(*env)->vars)
	{
		printf("Environment error\n");
		return (0);
	}
	correct_node = get_value((*env)->vars, "PWD");
	while (correct_node->value[i] != '\0')
	{
		ft_putchar_fd(correct_node->value[i], 2);
		i++;
	}
	return (0);
}
