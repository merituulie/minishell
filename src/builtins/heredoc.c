/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonseonlee <yoonseonlee@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 07:50:19 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/27 19:26:41 by yoonseonlee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/parsing.h"
#include "../../libft/libft.h"

static int	find_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

//SIGNAL IS NOT HANDLED YET.
//cat << DELIM case is not handled yet.
/*here_doc with signal needs to be handled.
also how to wait for the cat command for example.
file is deleted with unlink function.*/
int	ft_heredoc(t_command *command)
{
	int		fd;
	char	*line;
	t_data	ms;

	g_info.sig_status = 0;
	fd = open("heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (fd == -1)
		printf("Error in heredoc file opening\n");
	line = readline("> ");
	while (line)
	{
		if (!ft_strncmp_all(line, command->input) || g_info.sig_status)
			break ;
		if (find_index(line, '$') != -1)
			line = expand_var(&ms, line, find_index(line, '$'));
		if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
			printf("heredoc writing error\n");
		free(line);
		line = NULL;
		line = readline("> ");
	}
	free(line);
	close(fd);
	if (unlink("heredoc.txt") != 0)
		printf("heredoc deleting error\n");
	return (fd);
}
