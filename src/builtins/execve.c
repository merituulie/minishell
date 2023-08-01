/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:07:09 by jhusso            #+#    #+#             */
/*   Updated: 2023/08/01 13:07:13 by jhusso           ###   ########.fr       */
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

static char	*find_cmd_path(char *cmd, t_node **head)
{
	char	*path;
	char	**split_path;

	path = get_value(head, "PATH")->value;
	split_path = ft_split(path, ':');
	if (split_path)
		path = access_path(split_path, cmd);
	free_char_array(split_path);
	return (path);
}

int	ft_execve(t_command *command, t_env **env)
{
	char	*path;
	char	**vars;

	path = find_cmd_path(command->command, (*env)->vars);
	if (!path)
		return (-1);
	vars = ft_split(env_to_string(env), '\n');
	if (execve(path, command->full_cmd, vars) < 0)
		ft_putstr_fd("Error with execve call!", 2);
	free_char_array(vars);
	return (0);
}
