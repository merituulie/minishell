/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:50:22 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/24 12:30:30 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	error_code(int number, t_env **env)
{
	t_node	*temp;
	char	*nbr;
	char	*new_key;

	new_key = ft_strdup("?");
	if (!new_key)
		printf("malloc_error\n");
	temp = *((*env)->vars);
	nbr = ft_itoa(number);
	if (!get_value(&temp, "?"))
		set_value(&temp, "?", nbr);
	else
	{
		temp = get_value(&temp, "?");
		temp->value = nbr;
	}
}
