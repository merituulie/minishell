/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:44:34 by emeinert          #+#    #+#             */
/*   Updated: 2023/08/01 15:11:04 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static	int	check_unset_input(char *input)
{
	int i;
	
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

static	void	unset_loop(char **loop, t_node *temp)
{
	int i;
	i = 0;
	while (loop[i])
	{
		if (check_unset_input(loop[i]) == 1)
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(loop[i], 2);
			return (ft_putstr_fd("': not a valid identifier\n", 2));
		}
		if (!get_value(&temp, loop[i]))
			i++;
		else
		{
			delete_value(&temp, loop[i]);
			i++;
		}
	}
}
void	ft_unset(char *input, t_env *env)
{
	t_node	*temp;
	char	**loop;

	temp = *env->vars;
	if (!input)
		return ;
	loop = ft_split(input, ' ');
	unset_loop(loop, temp);
	ft_free_array(loop);
}
