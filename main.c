/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/17 12:49:25 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf, perror
#include "headers/parsing.h"
#include "headers/lexer.h"
#include "headers/env.h"
#include "headers/minishell.h"
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**cmd_line;
	int		i;
	int		j;
	t_data	ms;
	t_command *cmd;

	(void)argc;
	(void)argv;
	line = readline(PINK "Jose's PinkShell: " BORING);
	cmd_line = ft_lexer(line);
	free(line);
	i = -1;
	while (cmd_line[++i])
		printf("cmd_line is: %s\n", cmd_line[i]);
	ms.env = NULL;
	fill_env(envp, &ms.env);
	ms.end = 0;
	ms.start = 0;
	ms.s_quotes = 0;
	ms.d_quotes = 0;
	cmd_line = expand_quote_check(&ms, cmd_line);
	cmd_line = concatenate(cmd_line, &ms);
	while (cmd_line[++i])
	i = -1;
	{
		printf("after parsing, cmd_line[%d] is %s\n", i, cmd_line[i]);
	}
	cmd = init_cmds(cmd_line);
	free_str_array(cmd_line);
	return (0);
}
