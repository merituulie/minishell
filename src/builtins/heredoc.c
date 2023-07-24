/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 07:50:19 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/21 14:02:49 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

//SIGNAL IS NOT HANDLED YET.
//cat << DELIM case is not handled yet.
/*here_doc with signal needs to be handled.
also how to wait for the cat command for example.
file is deleted with unlink function.*/
int	ft_heredoc(t_command *command)
{
	int		fd;
	char	*line;

	fd = open("heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (fd == -1)
		printf("Error in heredoc file opening\n");
	line = readline("> ");
	while (line)
	{
		if (!ft_strncmp_all(line, command->input))
			break ;
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
