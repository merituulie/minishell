/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:54:29 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:54:30 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_export_env(t_env **env)
{
	char	**export;
	int		i;

	export = ft_split(env_to_string(env), '\n');
	if (!export)
		return ;
	i = 0;
	while (export[i])
	{
		if (export[i][0] != '\0')
		{
			ft_putstr_fd("declare -x ", 1, 0);
			ft_putstr_fd(export[i], 1, 0);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	ft_free_array(export);
}

static void	copy_keyvalue(char **output, t_node *node)
{
	char	*temp;

	if (!output || !*output)
		temp = ft_strjoin(node->key, "");
	else
		temp = ft_strjoin(*output, node->key);
	temp = ft_strjoin(temp, "=");
	temp = ft_strjoin(temp, node->value);
	temp = ft_strjoin(temp, "\n");
	free(*output);
	*output = temp;
}

char	*env_to_string(t_env **env)
{
	char	*output;
	t_node	*temp_node;

	temp_node = *(*env)->vars;
	output = NULL;
	while (temp_node)
	{
		copy_keyvalue(&output, temp_node);
		temp_node = temp_node->next;
	}
	return (output);
}

void	ft_env(t_env **env, t_command *command)
{
	if (command->input || command->flags)
	{
		ft_putstr_fd(command->command, 2, 1);
		ft_putstr_fd(": ", 2, 0);
		ft_putstr_fd(command->full_cmd[1], 2, 0);
		ft_putstr_fd(": no such file or directory\n", 2, 0);
		set_exit_code(127);
		exit(g_info.exit_code);
	}
	ft_putstr_fd(env_to_string(env), 1, 0);
	set_exit_code(0);
}
