/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmameinert <emmameinert@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:57:40 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/30 08:42:38 by emmameinert      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

//first time when cd is called, oldPWD is created, from second onwards, update.
//error code 1

/*chdir changes the current working directory to dirctory path that is given.
chdir returns 0 if successful, 1 if not.
go_dir function will chdir with the arguments that is given*/
static void	go_dir(t_env **env, t_command *command)
{
	t_node	*temp;

	temp = *((*env)->vars);
	if (command->input == NULL)
	{
		temp = get_value((*env)->vars, "HOME");
		if (!temp)
			error_msg(1, "HOME not set\n", command);
		else if (chdir(temp->value))
			error_msg(1, "can't move to HOME directory\n", command);
	}
	else if (chdir(command->full_cmd[1]))
		error_msg(1, "No such file or directory\n", command);
}

/*when cd function is called, OLDPWD is created in env.
After create the OLDPWD, update PWD and return from
the function. cd, cd ., cd .. cases are handled*/
void	ft_cd(t_command *command, t_env **env)
{
	char	*old_pwd;
	t_node	*temp;

	temp = *(*env)->vars;
	old_pwd = ft_strdup(getcwd(NULL, 0));
	if (!old_pwd)
		perror("PWD doesn't exist");
	if (get_value((*env)->vars, "OLDPWD") == NULL)
		set_value((*env)->vars, "OLDPWD", old_pwd);
	else
	{
		temp = get_value(&temp, "OLDPWD");
		temp->value = ft_strdup(old_pwd);
		if (!temp->value)
			printf("allocation fail!\n");
	}
	go_dir(env, command);
	temp = NULL;
	temp = get_value((*env)->vars, "PWD");
	temp->value = getcwd(NULL, 0);
	if (!temp->value)
		printf("allocation fail!\n");
}
