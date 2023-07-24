/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:06:45 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/24 11:50:11 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static t_env	*init_env(void)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(*env));
	if (!env)
		ft_putstr_fd("Cannot allocate memory\n", 2);
	return (env);
}

void	fill_env(char **envp, t_env **env)
{
	char	**key_value;
	int		i;

	(*env) = init_env();
	i = 0;
	while (envp[i])
	{
		key_value = ft_split(envp[i], '=');
		if (key_value == NULL)
			ft_putstr_fd("Cannot allocate memory\n", 2);
		(*env)->vars = set_value((*env)->vars, key_value[0], key_value[1]);
		if ((*env)->vars == NULL)
			ft_putstr_fd("Cannot allocate memory\n", 2);
		free(key_value);
		i++;
	}
}
