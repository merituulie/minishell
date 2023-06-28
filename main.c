/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/06/20 13:23:23 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/minishell.h"
#include "./headers/hashmap.h"
#include "./headers/env.h"
#include "libft/libft.h"

// int	main(void)
// {
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	if (argc > 2 || !argv[1])
		return (0);
	if (ft_strncmp(argv[1], "env", 3) == 0)
		ft_env(envp);
	else
		printf("Error, command not found\n");
	return (0);
}