/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:39:58 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/11 15:09:09 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*if isPiped = 1, we dont need to print anything,
we just return whatever the output of the current command is
so that the next command can take it as input.*/
/* just printing input or otherwise itll complain */
static char	*handle_command(t_command *command,
			t_command *next, t_env **env)
{
	if (ft_strncmp(command->command, "env", 3) == 0)
		return (ft_env(env, next));
	else if (ft_strncmp(command->command, "echo", 4) == 0)
		return (NULL);
	else if (ft_strncmp(command->command, "cd", 2) == 0)
		return (NULL);
	else if (ft_strncmp(command->command, "pwd", 3) == 0)
		return (NULL);
	else if (ft_strncmp(command->command, "export", 6) == 0)
		return (NULL);
	else if (ft_strncmp(command->command, "unset", 5) == 0)
		return (NULL);
	else if (ft_strncmp(command->command, "exit", 4) == 0)
		return (NULL);
	else
	{
		return (NULL);
	}
	return (NULL);
}
		/* if the command given is none of our own ones,
			we use execp or whatever it is to use the actual command here
			and return the output of that? */

int	handle_commands(t_command *commands, t_env **env)
{
	while (commands)
	{
		if (commands + 1)
			handle_command(commands, commands + 1, env);
		else
			handle_command(commands, NULL, env);
		commands++;
	}
	return (0);
}
