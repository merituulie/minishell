/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:39:58 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/12 16:33:47 by emeinert         ###   ########.fr       */
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
	if (ft_strncmp_all(command->command, "env") == 0)
		return (ft_env(env, next));
	else if (ft_strncmp_all(command->command, "echo") == 0)
		return (NULL);
	else if (ft_strncmp_all(command->command, "cd") == 0)
		return (NULL);
	else if (ft_strncmp_all(command->command, "pwd") == 0)
		return (NULL);
	else if (ft_strncmp_all(command->command, "export") == 0)
		return (NULL);
	else if (ft_strncmp_all(command->command, "unset") == 0)
		return (NULL);
	else if (ft_strncmp_all(command->command, "exit") == 0)
		return (NULL);
	else
	{	
		command_execution(command->command, env);
	}
	return (NULL);
}

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
