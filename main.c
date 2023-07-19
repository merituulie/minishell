/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/19 10:22:29 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"
#include "headers/lexer.h"
#include "headers/env.h"
#include "headers/minishell.h"
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

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
	ms.i = -1;
	ms.env = NULL;
	fill_env(envp, &ms.env);
	cmd_line = expand_quote_check(&ms, cmd_line);
	cmd_line = concatenate(cmd_line, &ms);
	ms.i = -1;
	cmd = init_cmds(cmd_line);
	ms.i = -1;
	while (cmd[++(ms.i)].command)
	{
		printf("cmd[%d].command is %s$\n", ms.i, cmd[ms.i].command);
		printf("cmd[%d].flags is %s$\n", ms.i, cmd[ms.i].flags);
		printf("cmd[%d].input is %s$\n", ms.i, cmd[ms.i].input);
		if (cmd[ms.i].full_cmd)
		{
			printf("cmd[%d].full_cmd[0] is %s\n", ms.i, cmd[ms.i].full_cmd[0]);
			printf("cmd[%d].full_cmd[1] is %s\n", ms.i, cmd[ms.i].full_cmd[1]);
			printf("cmd[%d].full_cmd[2] is %s\n", ms.i, cmd[ms.i].full_cmd[2]);
		}
	}
	// handle_commands(cmd, &env); to send env, we need to have env_struct in the minishell header.
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
	if (cmd_line)
		free_str_array(cmd_line);
	return (0);
}
