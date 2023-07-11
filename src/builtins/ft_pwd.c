/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:08:29 by rmakinen          #+#    #+#             */
/*   Updated: 2023/07/11 08:18:06 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"
#include "../../headers/env.h"
#include "../../headers/hashmap.h"

char	*ft_pwd(t_env *env, int isPiped)
{
	t_node	*correct_node;

	if (!env->vars)
	{
		printf("Environment error\n");
		return (NULL);
	}
	correct_node = get_value(env->vars, "PWD");
	if (isPiped == 0)
	{
		printf("%s", correct_node->value);
		return (NULL);
	}
	else
		return (correct_node->value);
}
