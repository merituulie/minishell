/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:50:22 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/24 11:05:43 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	we_exit(int number, t_env *env)
{
	t_node	*temp;
	char	*nbr;

	temp = *env->vars;
	nbr = ft_itoa(number);
	if (!get_value(&temp, "?"))
		set_value(&temp, "?", nbr);
	else
	{
		temp = get_value(&temp, "?");
		temp->value = nbr;
	}
	exit(number);
}
