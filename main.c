/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/17 13:22:35 by yoonslee         ###   ########.fr       */
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
	while (cmd_line[++(ms.i)])
		printf("cmd_line is: %s\n", cmd_line[ms.i]);
	ms.env = NULL;
	fill_env(envp, &ms.env);
	cmd_line = expand_quote_check(&ms, cmd_line);
	cmd_line = concatenate(cmd_line, &ms);
	ms.i = -1;
	while (cmd_line[++(ms.i)])
	{
		printf("after parsing, cmd_line[%d] is %s$\n", ms.i, cmd_line[ms.i]);
	}
	cmd = init_cmds(cmd_line);
	ms.i = -1;
	while (cmd[++(ms.i)].command)
	{
		printf("cmd[%d].command is %s$\n", ms.i, cmd[ms.i].command);
		printf("cmd[%d].flags is %s$\n", ms.i, cmd[ms.i].flags);
		printf("cmd[%d].input is %s$\n", ms.i, cmd[ms.i].input);
	}
	free_str_array(cmd_line);
	return (0);
}
