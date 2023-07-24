/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:50:22 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/24 15:07:37 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	reset_error_code(t_env **env)
{
	t_node	*temp;
	char	*key;
	char	*value;

	key = ft_strdup("?");
	if (!key)
		printf("malloc_error\n");
	temp = *((*env)->vars);
	value = ft_strdup("0");
	if (!get_value(&temp, key))
		set_value(&temp, key, value);
	else
	{
		temp = get_value(&temp, key);
		temp->value = value;
	}
}


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
