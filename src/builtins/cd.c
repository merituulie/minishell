/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:57:40 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/01 11:39:18 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	print_command(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i].command)
	{
		if (cmd[i].command)
			printf("cmd[%d].command is %s$\n", i, cmd[i].command);
		if (cmd[i].full_cmd[0])
			printf("cmd[%d].full_cmd[0] is %s$\n", i, cmd[i].full_cmd[0]);
		if (cmd[i].full_cmd[1])
			printf("cmd[%d].full_cmd[1] is %s$\t%p\n", i, cmd[i].full_cmd[1], &(*cmd[i].full_cmd[1]));
		if (cmd[i].flags)
			printf("cmd[%d].flags is %s$\n", i, cmd[i].flags);
		if (cmd[i].input)
			printf("cmd[%d].input is %s$\t%p\n", i, cmd[i].input, &(*cmd[i].input));
		if (cmd[i].infile_name)
			printf("cmd[%d].infile is %s$\n", i, cmd[i].infile_name);
		if (cmd[i].outfile_name)
			printf("cmd[%d].outfile is %s$\n", i, cmd[i].outfile_name);
	}
}

//first time when cd is called, oldPWD is created, from second onwards, update.
//error code 1

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

/*chdir changes the current working directory to dirctory path that is given.
chdir returns 0 if successful, 1 if not.
go_dir function will chdir with the arguments that is given*/
static void	go_dir(t_env **env, t_command *command)
{
	t_node	*temp;
	char	*path;

	temp = *((*env)->vars);
	// printf("temp = %p\n", &(*temp));
	if (command->input == NULL)
	{
		temp = get_value((*env)->vars, "HOME");
		if (!temp)
			error_msg(1, "HOME not set\n", command);
		else if (chdir(temp->value))
			error_msg(1, "can't move to HOME directory\n", command);
	}
	else
	{
		path = get_path(command->full_cmd[1]);
		if (chdir(path))
			error_msg(1, "No such file or directory\n", command);
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
		set_value((*env)->vars, "OLDPWD", old_pwd);
	else
	{
		temp = get_value(&temp, "OLDPWD");
		free(temp->value);
		temp->value = old_pwd;
	}
	// free(old_pwd);
	print_command(command);
	go_dir(env, command);
	temp = NULL;
	temp = get_value((*env)->vars, "PWD");
	printf("temp value = %s\t%p\n", temp->value, &(*temp->value));
	free(temp->value);
	temp->value = getcwd(NULL, 0);
	if (!temp->value)
		printf("allocation fail!\n");
}
