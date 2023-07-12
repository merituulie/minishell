#include "../headers/minishell.h"

static char	*access_path(char **path, char *cmd)
{
	char	*passing;
	char	*onepart;
	int		i;

	i = -1;
	while (path[++i] != NULL)
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

static char	*find_path(char *cmd, t_node **head)
{
	t_node *env_path;
	char *path;
	char **split_path;

	env_path = get_value(head, "PATH");
	path = env_path->value;
	split_path = ft_split(path, ':');
	if (split_path != NULL)
		path = access_path(split_path, cmd);
	freemystuff(split_path);
	return (path);
}

int command_execution(char *cmd, t_env **env, int fd, int isPiped)
{
	t_env *temp;
	char *path;

	temp = *env;
	path = find_path(cmd, temp->vars);
	if (!path)
		return (NULL);
	execve(path, cmd, temp->vars); 
	return (fd);
}