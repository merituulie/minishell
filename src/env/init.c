/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:06:45 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/13 12:53:56 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"
#include "../../headers/env.h"

static t_env	*init_env(void)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(*env));
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
		(*env)->vars = set_value((*env)->vars, key_value[0], key_value[1]);
		free(key_value);
		i++;
	}
}
