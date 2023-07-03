/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:39:58 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/03 19:48:42 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// if isPiped = 1, we dont need to print anything,
// we just return whatever the output of the current command is
// so that the next command can take it as input.
static char	*handle_command(t_command *command,
			t_env **env, char *input, int isPiped)
{
	if (!input)
		printf("%s", input); // just printing here or otherwise itll complain
	if (ft_strncmp(command->command, "env", 3) == 0)
		return (ft_env(env, isPiped));
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
		/* if the command given is none of our own ones,
			we use execp or whatever it is to use the actual command here
			and return the output of that? */
	}
	return (NULL);
}

int	handle_commands(t_command *commands[], t_env **env)
{
	int			i;
	t_command	*next;
	char		*output;

	i = 0;
	output = NULL;
	while (commands[i])
	{
		next = commands[i + 1];
		if (next)
			output = handle_command(commands[i], env, output, 1);
		else
			output = handle_command(commands[i], env, output, 0);
		i++;
	}
	return (0);
}
