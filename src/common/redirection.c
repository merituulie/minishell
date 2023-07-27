/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:26:21 by rmakinen          #+#    #+#             */
/*   Updated: 2023/07/27 15:20:55 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

int	open_redir_files(t_command cmd, char *str)
{
	if (!ft_strncmp_all("<", cmd.command))
	{
		cmd.infile_name = ft_strdup(str);
		if (!cmd.infile_name)
			printf("strdup allocation fail!\n");
		cmd.fds[1] = open_file(cmd.infile_name, O_RDONLY);
	}
	else if (!ft_strncmp_all(">", cmd.command))
	{
		cmd.outfile_name = ft_strdup(str);
		if (!cmd.outfile_name)
			printf("strdup allocation fail!\n");
		cmd.fds[0] = open_file(cmd.outfile_name, O_CREAT | O_WRONLY | O_TRUNC);
	}
	else if (!ft_strncmp_all(">>", cmd.command))
	{
		cmd.outfile_name = ft_strdup(str);
		if (!cmd.outfile_name)
			printf("strdup allocation fail!\n");
		cmd.fds[0] = open_file(cmd.outfile_name, O_CREAT | O_WRONLY | O_APPEND);
	}
	return (0);
}
