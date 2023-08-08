/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:08:29 by rmakinen          #+#    #+#             */
/*   Updated: 2023/08/08 13:46:36 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

int	ft_pwd(t_env *env)
{
	t_node	*correct_node;

	if (!env->vars)
	{
		ft_putstr_fd("Environment error.\n", 2, 1);
		return (1);
	}
	correct_node = get_value(env->vars, "PWD");
	ft_putstr_fd(correct_node->value, 1, 0);
	ft_putchar_fd('\n', 1);
	return (0);
}
