/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:08:29 by rmakinen          #+#    #+#             */
/*   Updated: 2023/07/31 09:53:47 by jhusso           ###   ########.fr       */
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
		printf("Environment error\n");
		return (1);
	}
	correct_node = get_value(env->vars, "PWD");
	ft_putstr_fd(correct_node->value, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
