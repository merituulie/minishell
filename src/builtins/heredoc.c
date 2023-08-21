/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 07:50:19 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/21 16:13:49 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	write_heredoc(char *delim, t_env **env, int fd)
{
	char	*line;
	t_data	ms;

	line = readline("> ");
	while (line)
	{
		if (((ft_strlen(line) == ft_strlen(delim)) \
		&& !ft_memcmp(line, delim, ft_strlen(line))) \
		|| g_info.sig_status)
			break ;
		if (find_index(line, '$') != -1)
			line = expand_var_here(&ms, line, find_index(line, '$'), env);
		if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
			ft_putstr_fd("Heredoc writing error.\n", 2, 1);
		free(line);
		line = NULL;
		line = readline("> ");
	}
	free(line);
}

int	ft_heredoc(t_command *command, t_env **env, char *delim)
{
	int		fd;

	g_info.sig_status = 0;
	fd = -1;
	if (command->infile_name && !ft_strncmp(command->infile_name, "HEREDOC", 7))
		fd = open_file(command->infile_name, O_CREAT | O_WRONLY | O_TRUNC);
	write_heredoc(delim, env, fd);
	close(fd);
	update_command_redir(command);
	set_exit_code(0);
	return (-1);
}
