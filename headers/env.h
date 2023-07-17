/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:55:08 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/13 13:18:56 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "hashmap.h"
# include "minishell.h"

typedef struct s_env
{
	struct s_node	**vars;
}	t_env;

void	fill_env(char **envp, t_env **env);
// void	*ft_env(t_env **env, t_command *next);

#endif
