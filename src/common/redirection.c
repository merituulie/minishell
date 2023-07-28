/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:26:21 by rmakinen          #+#    #+#             */
/*   Updated: 2023/07/28 12:10:23 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

int	open_redir_files(t_command *cmd, int track, char *str, char *input)
{
	printf("open_redir: str is %s\n", str);
	printf("open_redir: input is %s\n", input);
	if (!ft_strncmp_all("<", input))
	{
		cmd[track].infile_name = ft_strdup(str);
		if (!cmd[track].infile_name)
			printf("strdup allocation fail!\n");
		close_file(0);
		cmd[track].fds[0] = open_file(cmd[track].infile_name, O_RDONLY);
		dup2(cmd[track].fds[0], 0);
	}
	else if (!ft_strncmp_all(">", input))
	{
		cmd[track].outfile_name = ft_strdup(str);
		if (!cmd[track].outfile_name)
			printf("strdup allocation fail!\n");
		close_file(1);
		cmd[track].fds[1] = open_file(cmd[track].outfile_name, O_CREAT | O_WRONLY | O_TRUNC);
		dup2(cmd[track].fds[1], 1);
	}
	else if (!ft_strncmp_all(">>", input))
	{
		cmd[track].outfile_name = ft_strdup(str);
		if (!cmd[track].outfile_name)
			printf("strdup allocation fail!\n");
		close_file(1);
		cmd[track].fds[1] = open_file(cmd[track].outfile_name, O_CREAT | O_WRONLY | O_APPEND);
		dup2(cmd[track].fds[1], 1);
	}
	return (0);
}
