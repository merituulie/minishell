/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/20 08:26:26 by rmakinen         ###   ########.fr       */
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

typedef struct s_command	t_command;

void	fill_env(char **envp, t_env **env);
void	ft_env(t_env **env, t_command *next);

#endif
