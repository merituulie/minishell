/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmameinert <emmameinert@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/27 11:11:36 by emmameinert      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"
#include "headers/lexer.h"
#include "headers/minishell.h"
#include "libft/libft.h"
#include <termios.h>

static void	print_cmd_line(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("cmd_line is %s\n", str[i]);
		i++;
	}
}

static void	print_command(t_command *cmd)
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

static void	print_full_command(t_command *cmd)
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

static void	add_shlvl(t_env **env)
{
	t_node *temp;
	int shlvl;
	
	temp = get_value((*env)->vars, "SHLVL");
	shlvl = ft_atoi_exit(temp->value);	
	temp->value = ft_itoa(shlvl + 1);
	printf("shvl: %d\n", ft_atoi_exit(temp->value));
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**cmd_line;
	t_data		ms;
	t_command	*cmd;
	struct termios	term;

	(void)argc;
	(void)argv;
	ms.env = NULL;
	fill_env(envp, &ms.env);
	add_shlvl(&ms.env);
	if (tcgetattr(STDIN_FILENO, &term) < 0)
    {
		perror("tcgetattr");
        return 1;
	}
	while (42)
	{
		line = readline(PINK "Jose's PinkShell: " BORING);
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		cmd_line = ft_lexer(line);
		free(line);
		cmd_line = expand_quote_check(&ms, cmd_line);
		cmd_line = concatenate(cmd_line, &ms);
		print_cmd_line(cmd_line);
		cmd = init_cmds(&ms, cmd_line);
		print_command(cmd);
		print_full_command(cmd);
		execute_commands(cmd, ms.struct_count, &ms.env);
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
	}
	return (0);
}
