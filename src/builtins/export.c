
#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static char	*find_key(char *cmd)
{
	char	*key;
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
		i++;
		if (cmd[i] == '=')
			flag = 1;
	}
	if (!flag)
		return (NULL);
	key = ft_calloc(i, sizeof(char));
	if (!key)
		return (NULL);
	key[i] = '\0';
	while (--i > -1)
		key[i] = cmd[i];
	return (key);
}

static char	*find_value(char *cmd)
{
	int		i;
	int		j;
	int		len;
	char	*value;

	i = 0;
	j = 0;
	while (cmd[i] != '=')
		i++;
	len = ft_strlen(cmd);
	value = ft_calloc((len - i), sizeof(char));
	if (!value)
		return (NULL);
	i += 1;
	while (i < len)
	{
		value[j] = cmd[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

void	ft_export(char *cmd, t_env *env)
{
	t_node		*temp;
	char		*new_key;
	char		*new_value;

	temp = *env->vars;
	new_key = find_key(cmd);
	if (!new_key)
		return ;
	new_value = find_value(cmd);
	if (!new_value)
		return ;
	if (!get_value(&temp, new_key))
		set_value(&temp, new_key, new_value);
	else
	{
		temp = get_value(&temp, new_key);
		temp->value = new_value;
	}
}

void	ft_unset(char *cmd, t_env *env)
{
	t_node	*temp;

	temp = *env->vars;
	if (!get_value(&temp, cmd))
		return ;
	else
		delete_value(&temp, cmd);
}
