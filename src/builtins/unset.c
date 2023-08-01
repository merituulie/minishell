/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:44:34 by emeinert          #+#    #+#             */
/*   Updated: 2023/07/31 16:44:57 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	ft_unset(char *cmd, t_env *env)
{
	t_node	*temp;

	temp = *env->vars;
	if (!get_value(&temp, cmd))
		return ;
	else
		delete_value(&temp, cmd);
}
