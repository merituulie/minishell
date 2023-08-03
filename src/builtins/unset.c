/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:44:34 by emeinert          #+#    #+#             */
/*   Updated: 2023/08/03 17:18:36 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static	int	check_unset_input(char *input)
{
	int	i;

	i = 0;
	if (ft_isdigit(input[0]) == 1)
		return (1);
	while (input[i] != '\0')
	{
		if(input[i] == '=')
			return (1);
		i++;
	}
	if (input[0] == '\0')
		return (1);
	return (0);
}

static	void	unset_loop(char **input, t_node *temp)
{
	int i;
	i = 0;
	while (input[i])
	{
		if (check_unset_input(input[i]) == 1)
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(input[i], 2);
			return (ft_putstr_fd("': not a valid identifier\n", 2));
		}
		if (!get_value(&temp, input[i]))
			i++;
		else
		{
			delete_value(&temp, input[i]);
			i++;
		}
	}
}
void	ft_unset(char **input, t_env *env)
{
	t_node	*temp;

	temp = *env->vars;
	if (!input || !*input)
		return ;
	unset_loop(input, temp);
}
