/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:25:17 by rmakinen          #+#    #+#             */
/*   Updated: 2023/07/20 18:09:15 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

/*
-takes in an array of strings, each index is a string from the command line.
-if the first string is "-n" echo adds a newline at the end of the last string.
-echo returns 0 if successfull and 1 if not.
*/

char	*ft_echo(t_command *command, int isPiped)
{
	int	new_line;
	int	i;

	new_line = 0;
	i = 0;
	if (isPiped == 1)
		return (command->flags);
	if (ft_strncmp(command->flags, "-n ", 3) == 0)
	{
		new_line = 1;
		i = 3;
	}
	while (command->flags[i] != '\0')
	{
		write(1, &command->flags[i], 1);
		i++;
	}
	if (new_line == 0 || command->flags == NULL)
		write(1, "\n", 1);
	return (0);
}
