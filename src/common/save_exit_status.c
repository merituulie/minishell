/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:50:22 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/24 11:39:15 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	error_code(int number, t_env **env)
{
	t_node	**temp;
	char	*nbr;

	temp = (*env)->vars;
	nbr = ft_itoa(number);
	printf("nbr is %s\n", nbr);
	if (!get_value(temp, "?"))
		set_value(temp, "?", nbr);
	else
	{
		(*temp) = get_value(temp, "?");
		(*temp)->value = nbr;
	}
}
