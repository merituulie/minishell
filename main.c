/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/06/20 15:28:12 by jhusso           ###   ########.fr       */
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
	tokens = ft_lexer(readline(PINK "Jose's PinkShell >> " BORING));

	while (tokens[i])
	{
		printf("%i = %s\n", i, tokens[i]);
		i ++;
	}
	return (0);
}
