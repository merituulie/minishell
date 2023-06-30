/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:25:17 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/30 09:41:28 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

/*
-takes in an array of strings, each index is a string from the command line.
-if the first string is "-n" echo adds a newline at the end of the last string.
-echo returns 0 if successfull and 1 if not.
*/

int	ft_echo(char **str)
{
	int	newline;
	int	i;
	int	j;

	if (!str)
		return (1);
	newline = 0;
	if (ft_strncmp(str[1], "echo", 5) == 0 && ft_strncmp(str[2], "-n", 3) == 0)
		newline = 1;
	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		write(1, " ", 1);
		while (str[i][j])
		{
			write(1, &str[i][j], 1);
			j++;
		}
		i++;
	}
	if (newline == 1)
		write(1, "\n", 1);
	return (0);
}
