/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/06 11:07:53 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/minishell.h"
#include "./headers/hashmap.h"
#include "./headers/env.h"
#include "libft/libft.h"

int    main(int argc, char **argv, char **envp)
{
    t_env *env;
    int flag = 0;
    env = NULL;
    if (argc > 1)
        fill_env(envp, &env);
    while (!flag)
    {
        if (ft_strncmp(argv[1], "PATH", 4) == 0)
			ft_pwd(&env, 0);
    }
    return (0);
}
