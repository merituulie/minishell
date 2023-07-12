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
			return (0);
		free(onepart);
		if (access(passing, X_OK) == 0)
			return (passing);
		else
			free(passing);
	}
	return (cmd);
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
		cmd = access_path(split_path, cmd);
	free(path);
	//freemystuff(pipex->myarg_path);
	return (cmd);
}

int command_execution(char *cmd, t_env **env, int fd, int isPiped)
{
	t_env *temp;

	temp = *env;
	cmd = find_path(cmd, temp->vars);

	return (cmd);
}