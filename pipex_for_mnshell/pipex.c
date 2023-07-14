/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:01 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/14 13:59:41 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	argv_check(char *argv, t_pipex *pipex)
{
	pipex->cmd1_argv = ft_split(argv, ' ');
	if (!pipex->cmd1_argv)
		error_alloc2(pipex->cmd1_argv);
	printf("command is %s\n", pipex->cmd1_argv[0]);
	// pipex->cmd2_argv = ft_split(argv[2], ' ');
	// if (!pipex->cmd2_argv)
	// 	error_alloc2(pipex->cmd2_argv);
	return (0);
}

void	find_path(t_pipex *pipex, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		else
			i++;
	}
	if (!envp[i])
		error_msg(pipex, 2);
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	if (!path)
		error_alloc(path);
	pipex->path = ft_split(path, ':');
	if (!pipex->path)
		error_alloc2(pipex->path);
	free(path);
}

char	*get_path(t_pipex *pipex, char **cmd)
{
	int		i;
	char	*path_tmp;
	char	*path_cmd;

	i = 0;
	if (access(cmd[0], X_OK) == 0)
		return (ft_strdup(cmd[0]));
	else
	{
		while (pipex->path[i])
		{
			path_tmp = ft_strjoin(pipex->path[i], "/");
			path_cmd = ft_strjoin(path_tmp, cmd[0]);
			free(path_tmp);
			if (!path_cmd)
				error_alloc(path_cmd);
			if (access(path_cmd, X_OK) == 0)
				return (path_cmd);
			free(path_cmd);
			path_cmd = NULL;
			i++;
		}
	}
	return (NULL);
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*pipex;
	int flag;
	int i = 0;
	int j = 0;

	flag = 0;
	if (argc < 2)
		return (ft_printf("wrong amounts of arguments\n"));
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		error_msg(pipex, 4);
	pipex->amount = argc - 1;
	pipex->pid = ft_calloc((pipex->amount), sizeof(int));
	pipex->tmpin = dup(0);
	pipex->tmpout = dup(0);
	while (argv[++i])
	{
		pipex->envp = envp;
		argv_check(argv[i], pipex);
		find_path(pipex, envp);
		pipex->cmd1_path = get_path(pipex, pipex->cmd1_argv);
		printf("found path, path is %s\n", pipex->cmd1_path);
		first_child_process(pipex, flag, j);
		flag++;
		waitpid(pipex->pid[j], NULL, 0);
		j++;
		free_all(pipex);
	}
	return (0);
}
