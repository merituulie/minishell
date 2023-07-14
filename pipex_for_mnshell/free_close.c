/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:54:10 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/14 13:05:02 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_all(t_pipex *pipex)
{
	if (pipex->path)
		free_str_array(pipex->path);
	if (pipex->cmd1_path)
		free(pipex->cmd1_path);
	if (pipex->cmd1_argv)
		free_str_array(pipex->cmd1_argv);
	// if (pipex->cmd2_path)
	// 	free(pipex->cmd2_path);
	// if (pipex->cmd2_argv)
	// 	free_str_array(pipex->cmd2_argv);
}

void	close_all(t_pipex *pipex)
{
	if (pipex->infile > 0)
		close(pipex->infile);
	if (pipex->outfile > 0)
		close(pipex->outfile);
	// if (pipex->fd[0] > 0)
	// 	close(pipex->fd[0]);
	// if (pipex->fd[1] > 0)
	// 	close(pipex->fd[1]);
}
