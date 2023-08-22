/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:56:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:56:30 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*access_path(char **path, char *cmd)
{
	char	*passing;
	char	*onepart;
	int		i;

	i = -1;
	while (path[++i])
	{
		onepart = ft_strjoin(path[i], "/");
		passing = ft_strjoin(onepart, cmd);
		if (!passing || !onepart)
			return (NULL);
		free(onepart);
		if (access(passing, X_OK) == 0)
			return (passing);
		else
			free(passing);
	}
	return (NULL);
}

static char	*find_cmd_path(char *cmd, t_node *temp)
{
	char	*path;
	char	**split_path;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = temp->value;
	split_path = ft_split(path, ':');
	if (split_path)
		path = access_path(split_path, cmd);
	free_char_array(split_path);
	return (path);
}

static void	cmd_is_dir(t_command *command, t_env **env)
{
	t_node	*temp;

	if (!ft_strncmp_all(command->command, "/home") \
		|| !ft_strncmp_all(command->command, "/bin") \
		|| !ft_strncmp_all(command->command, "/"))
	{
		ft_puterror(126, ": is a directory\n", command);
		exit(126);
	}
	temp = check_value((*env)->vars, command->command);
	if (temp && command->command && command->command[0] == '/')
	{
		ft_puterror(126, ": is a directory\n", command);
		exit(126);
	}
	else
		return ;
}

int	execute_ft_execve(t_command *command, t_env **env)
{
	int	exec;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	exec = ft_execve(command, env);
	if (exec < 0)
	{
		if (exec == -1)
			ft_puterror(127, ": command not found\n", command);
		else if (exec == -2)
			ft_puterror(127, ": no such file or directory\n", command);
		exit(127);
	}
	exit(0);
}

int	ft_execve(t_command *command, t_env **env)
{
	char	*path;
	char	**vars;
	t_node	*temp;

	cmd_is_dir(command, env);
	cmd_is_not_executable(command);
	temp = get_value((*env)->vars, "PATH");
	if (!temp || (ft_strchr(command->command, '/') && \
		access(command->command, F_OK) == -1))
		return (-2);
	path = find_cmd_path(command->command, temp);
	if (!path || !ft_strncmp_all(path, ".."))
		return (-1);
	vars = ft_split(env_to_string(env), '\n');
	if (execve(path, command->full_cmd, vars) < 0)
	{
		ft_putstr_fd("Error with execution\n", 2, 1);
		exit (1);
	}
	free_char_array(vars);
	return (0);
}
