/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:56:54 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:56:57 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	exp_unset_exit_msg(char *input, int command)
{
	if (command == 2)
	{
		ft_putstr_fd("exit: ", 2, 1);
		ft_putstr_fd(input, 2, 0);
		ft_putstr_fd(": numeric argument required\n", 2, 0);
		return ;
	}
	else if (command == 1)
		ft_putstr_fd("export: '", 2, 1);
	else if (command == 0)
		ft_putstr_fd("unset: '", 2, 1);
	ft_putstr_fd(input, 2, 0);
	ft_putstr_fd("': not a valid identifier\n", 2, 0);
	set_exit_code(1);
}

static int	check_unset_input(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (1);
	if (!ft_isalpha(input[0]) && input[0] != '_')
		return (1);
	while (input[i] != '\0')
	{
		i++;
		if (!ft_isalnum(input[i]) && input[i] != '_' && input[i])
			return (1);
	}
	if (input[0] == '\0')
		return (1);
	return (0);
}

static	void	unset_loop(char **input, t_node *temp)
{
	int	i;

	i = 0;
	set_exit_code(0);
	while (input[i])
	{
		if (check_unset_input(input[i]) == 1)
			exp_unset_exit_msg(input[i], 0);
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
