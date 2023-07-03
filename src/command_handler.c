/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:39:58 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/03 13:44:21 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/env.h"

// if isPiped = 1, we dont need to print anything, we just return whatever the output of the current command is
// so that the next command can take it as input.
static char	*handle_command(t_command *command, t_env **env, char *input, int isPiped)
{
	if (ft_strncmp(command->command, "env", 3) == 0)
	{
		// function call to our env implementation
		return (NULL); // here we would actually return the env struct stuff as a string ready to be printed?
	}
	else if (ft_strncmp(command->command, "echo", 4) == 0)
	{
		// function call to echo with the -n flag
		return (NULL); // here we would actually return the echo output string ready to be printed
	}
	else if (ft_strncmp(command->command, "cd", 2) == 0)
	{
		// well here we have to actually move the location so, interesting to see how this works
		return (NULL); // we might need to handle this a different way.. or not!
	}
	else if (ft_strncmp(command->command, "pwd", 3) == 0)
	{
		// function call to our pwd implementation
		return (NULL); // here we would actually return the pwd output string ready to be printed
	}
	else if (ft_strncmp(command->command, "export", 6) == 0)
	{
		// function call to export impl, do the things we need to aaand
		return (NULL); // here we would actually return the export output (?) string ready to be printed
	}
	else if (ft_strncmp(command->command, "unset"), 5 == 0)
	{
		// function call to unset impl, do the things we need to aaand
		return (NULL); // here we would actually return the unset output (?) string ready to be printed
	}
	else if (ft_strncmp(command->command, "exit", 4) == 0)
	{
		// function call to exit impl, do the things we need to
		return (NULL);
	}
	else
	{
		// if the command given is none of our own ones,
		// we use execp or whatever it is to use the actual command here
		// and return the output of that?
	}
	return (NULL);
}

int handle_commands(t_command **commands, t_env **env)
{
	int 	i;
	char	*output;

	i = 0;
	output = NULL;
	while (commands[i])
	{
		if (commands[i + 1])
		{
			if (output)
				output = handle_command(&commands[i], output, env, 1);
			else
				output = handle_command(&commands[i], NULL, env, 1);
		}
		else
		{
			if (output)
				output = handle_command(&commands[i], output, env, 0);
			else
				output = handle_command(&commands[i], NULL, env, 0);
		}
		i++;
	}
	return (0);
}
