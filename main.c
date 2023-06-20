/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/06/20 14:51:45 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/minishell.h"
#include "./headers/hashmap.h"
#include "./headers/lexer.h"


int main(void)
{
	char	**tokens;
	// int delim = 9;

	int i = 0;
	tokens = lexer(readline(PINK "Jose's PinkShell >> " BORING));
	// // printf("%s\n", av[1]);
	while (tokens[i])
	{
		printf("%i = %s\n", i, tokens[i]);
		i ++;
	}
	return (0);
}
