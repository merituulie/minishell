/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:57:40 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/21 16:07:43 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*first time when cd is called, oldPWD is created, from second onwards, update.
error code 1*/
static char	*get_path(char *command_input)
{
	char	*path;
	int		end;

	end = 0;
	while (command_input[end] != '\0' && command_input[end] != ' ')
		end++;
	path = ft_substr(command_input, 0, end);
	return (path);
}

static void	cd_error_msg(t_command *command, char *str)
{
	ft_putstr_fd("cd: ", 2, 1);
	ft_putstr_fd(command->full_cmd[1], 2, 0);
	ft_putstr_fd(str, 2, 0);
}

/*chdir changes the current working directory to dirctory path that is given.
chdir returns 0 if successful, 1 if not.
go_dir function will chdir with the arguments that is given*/
static void	go_dir(t_env **env, t_command *command)
{
	t_node	*temp;
	char	*path;

	temp = *((*env)->vars);
	if (command->full_cmd[1] == NULL)
	{
		temp = get_value((*env)->vars, "HOME");
		if (!temp)
			ft_puterror(1, "HOME not set\n", command);
		else if (chdir(temp->value))
			ft_puterror(1, "can't move to HOME directory\n", command);
	}
	else
	{
		path = get_path(command->full_cmd[1]);
		if (chdir(path))
		{
			cd_error_msg(command, " : No such file or directory\n");
			set_exit_code(1);
		}
		else
			set_exit_code(0);
		free(path);
	}
}

/*when cd function is called, OLDPWD is created in env.
After create the OLDPWD, update PWD and return from
the function. cd, cd ., cd .. cases are handled*/
void	ft_cd(t_command *command, t_env **env)
{
	char	*old_pwd;
	t_node	*temp;

	temp = *(*env)->vars;
	old_pwd = getcwd(NULL, 0);
	if (get_value((*env)->vars, "OLDPWD") == NULL)
		set_value((*env)->vars, ft_strdup("OLDPWD"), old_pwd);
	else
	{
		temp = get_value(&temp, "OLDPWD");
		free(temp->value);
		temp->value = old_pwd;
	}
	go_dir(env, command);
	temp = NULL;
	temp = get_value((*env)->vars, "PWD");
	if (!temp)
	{
		set_value((*env)->vars, ft_strdup("PWD"), getcwd(NULL, 0));
		return ;
	}
	free(temp->value);
	temp->value = getcwd(NULL, 0);
	if (!temp->value)
		malloc_error();
}
