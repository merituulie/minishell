/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/31 11:51:55 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"
#include "headers/lexer.h"
#include "headers/minishell.h"
#include "libft/libft.h"
#include <termios.h>

// static void	print_cmd_line(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		printf("cmd_line is %s\n", str[i]);
// 		i++;
// 	}
// }

// static void	print_command(t_command *cmd)
// {
// 	int	i;

// 	i = -1;
// 	while (cmd[++i].command)
// 	{
// 		if (cmd[i].command)
// 			printf("cmd[%d].command is %s$\n", i, cmd[i].command);
// 		if (cmd[i].full_cmd[0])
// 			printf("cmd[%d].full_cmd[0] is %s$\n", i, cmd[i].full_cmd[0]);
// 		if (cmd[i].full_cmd[1])
// 			printf("cmd[%d].full_cmd[1] is %s$\n", i, cmd[i].full_cmd[1]);
// 		if (cmd[i].flags)
// 			printf("cmd[%d].flags is %s$\n", i, cmd[i].flags);
// 		if (cmd[i].input)
// 			printf("cmd[%d].input is %s$\n", i, cmd[i].input);
// 		if (cmd[i].infile_name)
// 			printf("cmd[%d].infile is %s$\n", i, cmd[i].infile_name);
// 		if (cmd[i].outfile_name)
// 			printf("cmd[%d].outfile is %s$\n", i, cmd[i].outfile_name);
// 	}
// }

// static void	print_full_command(t_command *cmd)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (cmd[++i].full_cmd)
// 	{
// 		j = 0;
// 		while (cmd[(i)].full_cmd[j])
// 		{
// 			printf("cmd[%d].full_cmd[%d] is %s\n", i, j, cmd[i].full_cmd[j]);
// 			j++;
// 		}
// 	}
// }

/* Might be logical to have as its own file in parser dir*/
t_command	*ft_parser(t_data *ms, char **cmd_line)
{
	t_command	*temp;

	cmd_line = expand_quote_check(ms, cmd_line);
	if (cmd_line == NULL)
		exit (-1);
	cmd_line = concatenate(cmd_line, ms);
	if (cmd_line == NULL)
		exit (-1);
	temp = init_cmds(ms, cmd_line);
	// print_command(temp);
	return (temp);
}

static void	free_cmd_struct(t_command *command, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (command[i].command)
			free (command[i].command);
		if (command[i].flags)
			free (command[i].flags);
		if (command[i].input)
			free (command[i].input);
		if (command[i].full_cmd)
			free_char_array(command[i].full_cmd);
		if (command[i].infile_name)
			free (command[i].infile_name);
		if (command[i].outfile_name)
			free (command[i].outfile_name);
		if (command[i].fds)
			free (command[i].fds);
	i++;
	}
	free (command);
}

static void	free_in_main(t_data *data)
{
	int	i;

	i = data->struct_count;
	while (data->i >= 0)
	{
		if (data[i].out)
			free(data[i].out);
		if (data[i].args)
			free_char_array(data[i].args);
		data->i--;
	}
	free(data);
}

void	minishell(t_data *ms)
{
	char		*line;
	char		**cmd_line;
	t_command	*cmd;

	while (42)
	{
		line = readline(PINK "Jose's PinkShell: " BORING);
		ctrl_d_cmd(line, ms);
		if (line[0] == '\n' || line[0] == '\0')
		{
			free (line);
			continue ;
		}
		else
			add_history(line);
		cmd_line = ft_lexer(line);
		if (cmd_line == NULL)
		{
			free (line);
			exit (-1);
		}
		free (line);
		cmd = ft_parser(ms, cmd_line);
		execute_commands(cmd, ms->struct_count, &ms->env);
		free_cmd_struct(cmd, ms->struct_count);
		free_char_array(cmd_line);
	}
	// rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_data	ms;

	(void)argc;
	(void)argv;
	ms.env = NULL;
	fill_env(envp, &ms.env);
	add_shlvl(&ms.env);
	set_signal_action(&ms);
	minishell(&ms);
	restore_terminal(&ms);
	free_in_main(&ms);
	return (0);
}


/*
- needs to be freed:
	t_data struct
	env
	something from shlvl?
*/
