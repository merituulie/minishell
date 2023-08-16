/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/08/15 17:52:03 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../headers/lexer.h"
#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	unlink_heredoc(char *filename)
{
	if (!ft_strncmp(filename, "HEREDOC", 7))
		unlink(filename);
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
			free(command[i].flags);
		if (command[i].input)
			free_char_array(command[i].input);
		if (command[i].full_cmd)
			free_char_array(command[i].full_cmd);
		if (command[i].infile_name)
		{
			unlink_heredoc(command[i].infile_name);
			free(command[i].infile_name);
		}
		if (command[i].outfile_name)
			free(command[i].outfile_name);
		i++;
	}
	if (command)
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

void	close_free_fd_arrays(void)
{
	if (g_info.redir_count > 0 && g_info.redir_fds)
	{
		close_files(g_info.redir_fds, g_info.redir_count);
		free(g_info.redir_fds);
		g_info.redir_fds = NULL;
	}
	if (g_info.pipe_count > 0 && g_info.pipe_fds)
	{
		free(g_info.pipe_fds);
		g_info.pipe_fds = NULL;
	}
}

void	free_in_minishell(t_command *cmd, int cmd_count)
{
	if (cmd != NULL)
		free_cmd_struct(cmd, cmd_count);
	close_free_fd_arrays();
}
