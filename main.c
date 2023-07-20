/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/20 11:33:05 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"
#include "headers/lexer.h"
#include "headers/env.h"
#include "headers/minishell.h"
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

void	print_cmd_line(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("cmd_line is %s\n", str[i]);
		i++;
	}
}

void	print_command(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i].command)
	{
		if (cmd[i].command)
			printf("cmd[%d].command is %s$\n", i, cmd[i].command);
		if (cmd[i].flags)
			printf("cmd[%d].flags is %s$\n", i, cmd[i].flags);
		if (cmd[i].input)
			printf("cmd[%d].input is %s$\n", i, cmd[i].input);
		if (cmd[i].infile_name)
			printf("cmd[%d].infile is %s$\n", i, cmd[i].infile_name);
		if (cmd[i].outfile_name)
			printf("cmd[%d].outfile is %s$\n", i, cmd[i].outfile_name);
	}
}	

void	print_full_command(t_command *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i].full_cmd)
	{
		j = 0;
		while (cmd[(i)].full_cmd[j])
		{
			printf("cmd[%d].full_cmd[%d] is %s\n", i, j, cmd[i].full_cmd[j]);
			j++;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**cmd_line;
	t_data		ms;
	t_command	*cmd;

	(void)argc;
	(void)argv;
	line = readline(PINK "Jose's PinkShell: " BORING);
	cmd_line = ft_lexer(line);
	free(line);
	ms.env = NULL;
	fill_env(envp, &ms.env);
	cmd_line = expand_quote_check(&ms, cmd_line);
	cmd_line = concatenate(cmd_line, &ms);
	print_cmd_line(cmd_line);
	cmd = init_cmds(&ms, cmd_line);
	print_command(cmd);
	print_full_command(cmd);
	// handle_commands(cmd, &env); to send env, we need to have env_struct in the minishell header.
	ms.i = ms.struct_count;
	while (ms.i >= 0)
	{
		if (cmd[ms.i].command)
			free(cmd[ms.i].command);
		if (cmd[ms.i].flags)
			free(cmd[ms.i].flags);
		if (cmd[ms.i].input)
			free(cmd[ms.i].input);
		ms.i--;
	}
	if (cmd)
		free(cmd);
	return (0);
}
