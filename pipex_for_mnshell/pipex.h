/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:12 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/14 13:14:33 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_pipex{
	char	**path;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_argv;
	char	**cmd2_argv;
	char	**envp;
	int		fd[2];
	int		infile;
	int		outfile;
	int		pid1[3];
	int		pid2;
	int		tmpin;
	int		tmpout;
}			t_pipex;

void	error_msg(t_pipex *pipex, int error_code);
void	error_alloc(char *str);
void	error_alloc2(char **str);
void	free_str_array(char **str);
void	free_all(t_pipex *pipex);
void	close_all(t_pipex *pipex);
void	first_child_process(t_pipex *pipex, int flag, int j);
void	second_child_process(t_pipex *pipex);
int		argv_check(char *argv, t_pipex *pipex);
void	find_path(t_pipex *pipex, char **envp);
char	*get_path(t_pipex *pipex, char **cmd);
int		main(int argc, char *argv[], char **envp);

#endif