/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:25:17 by rmakinen          #+#    #+#             */
/*   Updated: 2023/07/07 10:15:12 by rmakinen         ###   ########.fr       */
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
	int	newline;
	int	i;

	newline = 0;
	i = 0;
	if (isPiped == 1)
		return (command->command_flags);
	if (ft_strncmp(command->command_flags, "-n ", 3) == 0)
	{
		newline = 1;
		i = 3;
	}
	while (command->command_flags[i] != '\0')
	{
		write(1, &command->command_flags[i], 1);
		i++;
	}
	if (newline == 0 || command->command_flags == NULL)
		write(1, "\n", 1);
	return (0);
}
