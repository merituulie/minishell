/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/08/16 10:40:21 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static char	*find_key_in_str(char *cmd)
{
	char	*key;
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	if (!ft_isalpha(cmd[0]) && cmd[i] != '_')
		return (NULL);
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
		i++;
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_' && cmd[i] != '=' && cmd[i])
			return (NULL);
		if (cmd[i] == '=')
			flag = 1;
	}
	if (!flag)
		return (cmd);
	key = ft_calloc(i + 1, sizeof(char));
	if (!key)
		return (NULL);
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
	if (!value)
		return (ft_putstr_fd("Memory allocation failure.\n", 2, 1));
	if (!get_value(&temp, key))
	{
		set_value(&temp, key, value);
	}
	else
	{
		temp = get_value(&temp, key);
		free(key);
		free(temp->value);
		temp->value = value;
	}
}

static	void	export_loop(char **input, t_node *temp)
{
	int		i;
	char	*new_key;
	char	*new_value;
	char	*temp_char;

	i = -1;
	set_exit_code(0);
	while (input[++i])
	{
		temp_char = find_key_in_str(input[i]);
		if (!temp_char)
			exp_unset_err_msg(input[i], 1);
		else if (ft_strncmp_all(temp_char, input[i]))
		{
			new_key = ft_strdup(temp_char);
			free(temp_char);
			temp_char = find_value_in_str(input[i]);
			new_value = ft_strdup(temp_char);
			change_node(temp, new_key, new_value);
			free(temp_char);
		}
	}
}

void	ft_export(char **input, t_env *env)
{
	t_node	*temp;

	temp = *env->vars;
	if (!input || !*input)
	{
		print_export_env(&env);
		return ;
	}
	export_loop(input, temp);
}
