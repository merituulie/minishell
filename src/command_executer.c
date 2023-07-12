#include "../headers/minishell.h"

static char	*access_path(char **path, char *cmd)
{
	char	*passing;
	char	*onepart;
	int		i;

	i = -1;
	while (pipex->myarg_path[++i] != NULL)
	{
		onepart = ft_strjoin(pipex->myarg_path[i], "/");
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

static char	*find_path(char *cmd, t_ **envp, t_pipex *pipex)
{
	pipex->envp_path = ft_strdup(check_path(envp));
	pipex->myarg_path = ft_split(pipex->envp_path, ':');
	if (pipex->myarg_path != NULL)
		cmd = access_path(pipex, cmd);
	free(pipex->envp_path);
	freemystuff(pipex->myarg_path);
	return (cmd);
}

int command_execution(char *cmd, t_env **env, int fd, int isPiped)
{
	t_node *env_path;
	t_env *temp;
	char *path;
	char **split_path;

	temp = *env;
	cmd = find_path(cmd, temp->vars);
	env_path = get_value(temp->vars, "PATH");
	path = env_path->value;
	split_path = ft_split(path, ':');
	if (split_path != NULL)
		cmd = access_path(split_path, cmd);
	free(path);
	//free(split_path);
	return (cmd);
	

}