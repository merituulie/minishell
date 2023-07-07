/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:50:18 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/07 13:05:45 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf, perror
#include "headers/parsing.h"
#include "libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**cmd_line;
	int		i;
	int		j;
	t_data	ms;

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
	j = -1;
	cmd_line = expand_quote_check(&ms, cmd_line, i, j);
	cmd_line = concatenate(cmd_line, &ms);
	i = -1;
	while (cmd_line[++i])
	{
		printf("cmd [%d] is %s\n", i, cmd_line[i]);
	}
	free_str_array(cmd_line);
	return (0);
}
