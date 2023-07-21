/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:57:40 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/21 10:59:45 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

//first time when cd is called, oldPWD is created, from second onwards, update.
//error code 1

/*chdir changes the current working directory to dirctory path that is given.
chdir returns 0 if successful, 1 if not.
go_dir function will chdir with the arguments that is given*/
static void	go_dir(t_env *env, char *arg)
{
	t_node	*temp;

	temp = *env->vars;
	printf("arg is %s\n", arg);
	if (!arg)
	{
		temp = get_value(env->vars, "HOME");
		if (chdir(temp->value))
			printf("can't find home/error");
	}
	else if (chdir(arg))
		printf("can't change to dir");
	printf("go_dir executed\n");
}

/*when cd function is called, OLDPWD is created in env.
After create the OLDPWD, update PWD and return from
the function. cd, cd ., cd .. cases are handled*/
void	ft_cd(t_command *command, t_env *env)
{
	char	**args;
	char	*old_pwd;
	t_node	*temp;

	temp = *env->vars;
	old_pwd = ft_strdup(getcwd(NULL, 0));
	if (!old_pwd)
		perror("PWD doesn't exist");
	if (!get_value(&temp, "OLDPWD"))
		set_value(&temp, ft_strdup("OLDPWD"), old_pwd);
	else
	{
		temp = get_value(&temp, "OLDPWD");
		temp->value = ft_strdup(old_pwd);
	}
	printf("temp->key is %s, temp->value is %s\n", temp->key, temp->value);
	args = ft_split(command->flags, 32);
	go_dir(env, args[1]);
	temp = *env->vars;
	temp = get_value(&temp, "PWD");
	temp->value = ft_strdup(getcwd(NULL, 0));
	printf("temp->key is %s, temp->value is %s\n", temp->key, temp->value);
	free(old_pwd);
}
