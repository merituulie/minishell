/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:56:26 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/14 14:03:20 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipex *pipex, int flag)
{
	if (flag % 2 == 0)
	{
		pipex->infile = open("infile", O_RDWR | O_CREAT, S_IRWXU);
		if (pipex->infile == -1)
			perror("Infile error!");
		pipex->outfile = open("outfile", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if (pipex->outfile == -1)
			perror("Outfile error!");
	}
	if (flag % 2 == 1)
	{
		pipex->infile = open("outfile", O_RDWR, S_IRWXU);
		if (pipex->infile == -1)
			perror("Infile error!");
		pipex->outfile = open("infile", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if (pipex->outfile == -1)
			perror("Outfile error!");
	}
	// if (flag % 2 == 0 && flag != 0) 
	// {
	// 	pipex->infile = dup(pipex->tmpin);
	// 	pipex->outfile = open("outfile", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	// 	if (pipex->outfile == -1)
	// 		perror("Outfile error!");
	// }
}

void	first_child_process(t_pipex *pipex, int flag,  int j)
{
	open_files(pipex, flag);
	printf("I came to child process\n");
	pipex->pid[j] = fork();
	printf("pipex->pid[%d], pid is %d\n", j, getpid());
	if (pipex->pid[j] < 0)
		error_msg(pipex, 3);
	if (pipex->pid[j] == 0)
	{
		printf("here %d\n", j);
		printf("flag: %d, outfile: %d\n", flag, pipex->outfile);
		printf("flag: %d, infile: %d\n", flag, pipex->infile); 
		if (j < pipex->amount - 1)
		{
			if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
				exit(1);
		}
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			exit(1);
		close_all(pipex);
		if (!pipex->cmd1_path)
		{
			ft_putstr_fd("command not found", 2);
			exit(126);
		}
		printf("path is %s\n", pipex->cmd1_path);
		if (execve(pipex->cmd1_path, pipex->cmd1_argv, pipex->envp) < 0)
		{
			perror("error, child1 execve failed");
			exit(1);
		}
	}
}

