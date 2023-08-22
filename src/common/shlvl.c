/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:54:10 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:54:11 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	unset_oldpwd(t_node **temp)
{
	if (get_value(temp, "OLDPWD"))
		delete_value(temp, "OLDPWD");
}

void	add_shlvl(t_env **env)
{
	t_node	*temp;
	int		shlvl;

	temp = get_value((*env)->vars, "SHLVL");
	shlvl = (int)ft_atoll(temp->value);
	if (shlvl < 0)
		shlvl = 0;
	free(temp->value);
	temp->value = ft_itoa(shlvl + 1);
	unset_oldpwd(&temp);
}
