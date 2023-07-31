
#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static char	*find_key_in_str(char *cmd)
{
	char	*key;
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	if (cmd[0] >= 48 && cmd[0] <= 57)
		return (NULL);
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

static char	*find_value_in_str(char *cmd)
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

static void	change_node(t_node *temp, char *key, char *value)
{
	if (!get_value(&temp, key))
			set_value(&temp, key, value);
	else
	{
		temp = get_value(&temp, key);
		temp->value = value;
	}
}
static	void	export_loop(char **loop, t_node *temp)
{
	int 		i;
	char		*new_key;
	char		*new_value;
	char 		*temp_char;

	i = 0;
	while (loop[i])
	{
		temp_char = find_key_in_str(loop[i]);
		new_key = ft_strdup(temp_char);
		if (!new_key)
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(loop[i], 2);
			return (ft_putstr_fd("': not a valid identifier\n", 2));
		}
		free(temp_char);
		temp_char = find_value_in_str(loop[i]);
		new_value = ft_strdup(temp_char);
		if (!new_value)
			return (ft_putstr_fd("input error\n", 2));
		free(temp_char);
		change_node(temp, new_key, new_value);
		i++;
	}
}

void	ft_export(char *cmd, t_env *env)
{
	t_node		*temp;
	char 		**loop;

	temp = *env->vars;
	if (!cmd)
	{
		print_export_env(&env);
		return ;
	}
	loop = ft_split(cmd, ' ');
	export_loop(loop, temp);
	ft_free_array(loop);
}
