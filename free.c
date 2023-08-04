/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/08/04 13:40:21 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"
#include "headers/lexer.h"
#include "headers/minishell.h"
#include "libft/libft.h"

static void	unlink_heredoc(char *filename)
{
	if (!ft_strncmp_all(filename, HEREDOC))
	{
		unlink(HEREDOC);
	}
	return ;
}

void	free_cmd_struct(t_command *command, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (command[i].command)
			free(command[i].command);
		if (command[i].flags)
			free (command[i].flags);
		if (command[i].input)
			free_char_array(command[i].input);
		if (command[i].full_cmd)
			free_char_array(command[i].full_cmd);
		if (command[i].infile_name)
		{
			unlink_heredoc(command->infile_name);
			free(command[i].infile_name);
		}
		if (command[i].outfile_name)
			free(command[i].outfile_name);
		i++;
	}
	free(command);
}

void	free_in_main(t_data *data)
{
	int	i;

	i = data->struct_count;
	while (data->i >= 0)
	{
		if (data[i].out)
			free(data[i].out);
		if (data[i].args)
			free_char_array(data[i].args);
		data->i--;
	}
	free(data);
}

void	free_in_minishell(t_command *cmd, int cmd_count, char **cmd_line)
{
	free_cmd_struct(cmd, cmd_count);
	free_char_array(cmd_line);
}
